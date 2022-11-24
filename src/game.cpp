#include "game.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

#define SDL_ERROR_CHECK(error) if (error) { throw std::runtime_error(SDL_GetError()); }

bool CanMove(const Position& current_position, const Position& new_position)
{
    // Check if the old and new position is the same
    if (current_position == new_position)
    {
        return false;
    }

    // TODO
    // Check if the new position is taken by the same color pieces


    // TODO casltling
    return true;
}

Game::Game()
    : testing_(false)
    , is_running_(false)
    , window_(nullptr)
    , renderer_(nullptr)
    , move_piece_sfx_(nullptr)
    , castle_king_side_(false)
    , castle_queen_side_(false)
{

}

Game::~Game()
{
    DestroyResources();
}

void Game::SetTesting(bool testing)
{
    testing_ = testing;
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Failed to initialize SDL=" << SDL_GetError();
        return false;
    }

    std::cout << "SDL initialized...\n";

    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Failed to create window=" << SDL_GetError();
        return false;
    }

    std::cout << "Window created...\n";

    renderer_= SDL_CreateRenderer(window, -1, 0); // TODO values to constants

    // Check if renderer was created successfully
    if (renderer_ == nullptr)
    {
        std::cerr << "Failed to create renderer=" << SDL_GetError();
        return false;
    }

    if (SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND))
    {
        std::cerr << "Failed to set render blend mode=" << SDL_GetError();
        return false;
    }

    std::cout << "Renderer created...\n";

    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNKS) == SOUND_ERROR)
    {
        std::cerr << "Failed to initialize audio=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    std::cout << "Audio initialized...\n";

    move_piece_sfx_ = Mix_LoadWAV("sounds/piece_move.wav");

    if (move_piece_sfx_ == nullptr)
    {
        std::cerr << "Failed to load sfx=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    std::cout << "Move piece SFX loaded...\n";

    LoadBoard(FEN_STARTING_BOARD);
    std::cout << "Board prepared...\n";

    is_running_ = true;
    std::cout << "Initialization finished.\n";

    return true;
}

bool Game::LoadBoard(const string& fen)
{
    // https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    // Starting position:
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    board_.clear();

    auto row = 0;
    auto column = 0;
    vector<shared_ptr<Piece>> row_with_pieces;

    for (auto c : fen)
    {
        // End adding pieces
        if (board_.size() >= BOARD_HEIGHT)
        {
            break;
        }

        // New row
        if (row_with_pieces.size() >= BOARD_WIDTH)
        {
            board_.emplace_back(row_with_pieces);
            row_with_pieces.clear();
            row++;
            column = 0;
            continue;
        }

        // empty pieces
        if (std::isdigit(c))
        {
            const auto empty_pieces = getIntFromChar(c);

            for (auto i = 0; i < empty_pieces; i++)
            {
                row_with_pieces.emplace_back(nullptr);
                column++;
            }

            continue;
        }

        auto piece = createPieceFromChar(c);
        piece->SetPosition({ column, row });
        row_with_pieces.emplace_back(std::move(piece));
        column++;
    }

    // Check if valid board
    for (const auto& row : board_)
    {
        if (row.size() != BOARD_WIDTH)
        {
            std::cerr << "Invalid board FEN=" << fen << '\n';
            return false;
        }
    }

    // TODO: add reading castling
    castle_king_side_ = true;
    castle_queen_side_ = true;

    return true;
}

void Game::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT)
        {
            std::cout << "Window closed, quitting...\n";
            is_running_ = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cout << "ESC pressed, quitting...\n";
            is_running_ = false;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // TODO different color chosen piece
            OnMousePressed(event);
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            OnMouseReleased(event);
        }

        std::cout << std::flush;
    }
}

void Game::Update()
{
    HandleEvents();
    RenderBoard();
}

void Game::RenderBoard()
{
    SDL_Rect rectangle;
    int error = 0;

    vector<Position> possible_moves;

    if (selected_piece_ != nullptr)
    {
        possible_moves = selected_piece_->GetLegalMoves(board_);
    }

    for (auto column = 0; column < BOARD_WIDTH; column++)
    {
        for (auto row = 0; row < BOARD_HEIGHT; row++)
        {
            rectangle.x = column * POSITION_WIDTH;
            rectangle.y = row * POSITION_HEIGHT;
            rectangle.h = POSITION_HEIGHT;
            rectangle.w = POSITION_WIDTH;

            // Piece background
            if ((column + row) % 2 == 0)
            {
                // Light BG
                error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_LIGHT_R, BOARD_COLOR_LIGHT_G, BOARD_COLOR_LIGHT_B, SDL_ALPHA_OPAQUE);
                SDL_ERROR_CHECK(error);

            }
            else
            {
                // Dark BG
                error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_DARK_R, BOARD_COLOR_DARK_G, BOARD_COLOR_DARK_B, SDL_ALPHA_OPAQUE);
                SDL_ERROR_CHECK(error);
            }

            error = SDL_RenderFillRect(renderer_, &rectangle);
            SDL_ERROR_CHECK(error);

            // Highlight possible moves if moving piece
            const auto find = std::find(possible_moves.begin(), possible_moves.end(), Position(column, row));
            if (find != possible_moves.end())
            {
                // Semi transparent BG
                error = SDL_SetRenderDrawColor(renderer_, POSSIBLE_MOVE_COLOR_R, POSSIBLE_MOVE_COLOR_G, POSSIBLE_MOVE_COLOR_B, ALPHA_COLOR_SEMI);
                SDL_ERROR_CHECK(error);

                error = SDL_RenderFillRect(renderer_, &rectangle);
                SDL_ERROR_CHECK(error);
            } 

            // Piece on board
            const auto& piece = board_[row][column];
            if (piece != nullptr)
            {
                error = SDL_RenderCopy(renderer_, piece->GetTexture(), nullptr, &rectangle);
                SDL_ERROR_CHECK(error);
            }
        }

        // Selected piece
        if (selected_piece_ != nullptr)
        {
            // Highlight selected piece
            const auto& selected_piece_position = selected_piece_->GetPosition();
            rectangle.x = selected_piece_position.column * POSITION_WIDTH;
            rectangle.y = selected_piece_position.row * POSITION_HEIGHT;

            // Semi transparent BG
            error = SDL_SetRenderDrawColor(renderer_, POSSIBLE_MOVE_COLOR_R, POSSIBLE_MOVE_COLOR_G, POSSIBLE_MOVE_COLOR_B, ALPHA_COLOR_SEMI);
            SDL_ERROR_CHECK(error);

            error = SDL_RenderFillRect(renderer_, &rectangle);
            SDL_ERROR_CHECK(error);

            SDL_GetMouseState(&rectangle.x, &rectangle.y);

            // Move mouse in the middle
            rectangle.x -= POSITION_WIDTH / 2;
            rectangle.y -= POSITION_HEIGHT / 2;

            // Transparent BG
            error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_TRANSPARENT_R, BOARD_COLOR_TRANSPARENT_G, BOARD_COLOR_TRANSPARENT_B, SDL_ALPHA_TRANSPARENT);
            SDL_ERROR_CHECK(error);

            // Piece texture
            error = SDL_RenderCopy(renderer_, selected_piece_->GetTexture(), nullptr, &rectangle);
            SDL_ERROR_CHECK(error);
        }
    }

    // Render frame
    SDL_RenderPresent(renderer_);
}

void Game::DestroyResources()
{
    // Destroy resources
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    Mix_FreeChunk(move_piece_sfx_);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
}

void Game::OnMousePressed(const SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        const auto column = event.button.x / POSITION_WIDTH;
        const auto row = event.button.y / POSITION_HEIGHT;

        std::cout << "selected=[" << column << ", " << row << "]" << '\n';

        selected_piece_ = std::move(board_[row][column]);
    }
}

void Game::OnMouseReleased(const SDL_Event& event)
{
    int error = 0;

    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if (selected_piece_ != nullptr)
        {
            const Position new_position{ event.button.x / POSITION_WIDTH, event.button.y / POSITION_HEIGHT };
            std::cout << "new=[" << new_position.column << ", " << new_position.row << "]" << '\n';

            const auto& possible_moves = selected_piece_->GetLegalMoves(board_);
            const auto find = std::find(possible_moves.begin(), possible_moves.end(), new_position);

            // Check if new position is valid
            if (find != possible_moves.end())
            {
                // Set piece to new position
                selected_piece_->SetPosition(new_position);
                board_[new_position.row][new_position.column] = std::move(selected_piece_);

                // Play SFX
                if (Mix_PlayChannel(SOUND_PLAY_CHANNEL, move_piece_sfx_, SOUND_NO_REPEAT) == SOUND_ERROR)
                {
                    throw std::runtime_error(Mix_GetError());
                }
            }
            else
            {
                // Set piece to old position
                const auto& old_position = selected_piece_->GetPosition();
                board_[old_position.row][old_position.column] = std::move(selected_piece_);
            }
        }
    }
}

bool Game::isRunning() const
{
    return is_running_;
}

const vector<vector<shared_ptr<Piece>>>& Game::GetBoard() const
{
    return board_;
}

vector<vector<shared_ptr<Piece>>>& Game::GetBoard()
{
    return board_;
}

const Piece& Game::GetPiece(const Position& position) const
{
    if (board_[position.column][position.row] == nullptr)
    {
        throw std::runtime_error("invalid position");
    }

    return *board_[position.column][position.row].get();
}

Piece& Game::GetPiece(const Position& position)
{
    if (board_[position.column][position.row] == nullptr)
    {
        throw std::runtime_error("invalid position");
    }

    return *board_[position.column][position.row].get();
}

shared_ptr<Piece> Game::createPieceFromChar(char c) const
{
    if (testing_)
    {
        return createPieceFromCharNoTexture(c);
    }

    switch (c)
    {
    case 'K':
        return std::make_shared<King>(PieceColor::White, renderer_, WHITE_KING_TEXTURE);
    case 'Q':
        return std::make_shared<Queen>(PieceColor::White, renderer_, WHITE_QUEEN_TEXTURE);
    case 'R':
        return std::make_shared<Rook>(PieceColor::White, renderer_, WHITE_ROOK_TEXTURE);
    case 'B':
        return std::make_shared<Bishop>(PieceColor::White, renderer_, WHITE_BISHOP_TEXTURE);
    case 'N':
        return std::make_shared<Knight>(PieceColor::White, renderer_, WHITE_KNIGHT_TEXTURE);
    case 'P':
        return std::make_shared<Pawn>(PieceColor::White, renderer_, WHITE_PAWN_TEXTURE);
    case 'k':
        return std::make_shared<King>(PieceColor::Black, renderer_, BLACK_KING_TEXTURE);
    case 'q':
        return std::make_shared<Queen>(PieceColor::Black, renderer_, BLACK_QUEEN_TEXTURE);
    case 'r':
        return std::make_shared<Rook>(PieceColor::Black, renderer_, BLACK_ROOK_TEXTURE);
    case 'b':
        return std::make_shared<Bishop>(PieceColor::Black, renderer_, BLACK_BISHOP_TEXTURE);
    case 'n':
        return std::make_shared<Knight>(PieceColor::Black, renderer_, BLACK_KNIGHT_TEXTURE);
    case 'p':
        return std::make_shared<Pawn>(PieceColor::Black, renderer_, BLACK_PAWN_TEXTURE);
    default:
        break;
    }

    throw std::runtime_error("Creating piece for invalid character=" + c);
}

shared_ptr<Piece> Game::createPieceFromCharNoTexture(char c) const
{
    switch (c)
    {
    case 'K':
        return std::make_shared<King>(PieceColor::White);
    case 'Q':
        return std::make_shared<Queen>(PieceColor::White);
    case 'R':
        return std::make_shared<Rook>(PieceColor::White);
    case 'B':
        return std::make_shared<Bishop>(PieceColor::White);
    case 'N':
        return std::make_shared<Knight>(PieceColor::White);
    case 'P':
        return std::make_shared<Pawn>(PieceColor::White);
    case 'k':
        return std::make_shared<King>(PieceColor::Black);
    case 'q':
        return std::make_shared<Queen>(PieceColor::Black);
    case 'r':
        return std::make_shared<Rook>(PieceColor::Black);
    case 'b':
        return std::make_shared<Bishop>(PieceColor::Black);
    case 'n':
        return std::make_shared<Knight>(PieceColor::Black);
    case 'p':
        return std::make_shared<Pawn>(PieceColor::Black);
    default:
        break;
    }

    throw std::runtime_error("Creating piece for invalid character=" + c);
}

int Game::getIntFromChar(char c) const
{
    return c - '0';
}
