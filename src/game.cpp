#include "game.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

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
    , mouse_position_(0, 0) // TODO incorrect ???
    , current_position_(0, 0) // TODO incorrect ???
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
        std::cerr << "Failed to create window=" << SDL_GetError();
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
        piece->SetPosition({ row, column });
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
                error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_LIGHT_R, BOARD_COLOR_LIGHT_G, BOARD_COLOR_LIGHT_B, ALPHA_COLOR_SOLID);
            }
            else
            {
                // Dark BG
                error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_DARK_R, BOARD_COLOR_DARK_G, BOARD_COLOR_DARK_B, ALPHA_COLOR_SOLID);
            }

            if (error)
            {
                throw std::runtime_error(SDL_GetError());
            }

            error = SDL_RenderFillRect(renderer_, &rectangle);

            if (error)
            {
                throw std::runtime_error(SDL_GetError());
            }

            // Piece on board
            const auto& piece = board_[row][column];
            if (piece != nullptr)
            {
                error = SDL_RenderCopy(renderer_, piece->GetTexture(), nullptr, &rectangle);

                if (error)
                {
                    throw std::runtime_error(SDL_GetError());
                }
            }
        }

        // Selected piece
        if (selected_piece_ != nullptr)
        {
            SDL_GetMouseState(&rectangle.x, &rectangle.y);

            // Transparent BG
            error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_TRANSPARENT_R, BOARD_COLOR_TRANSPARENT_G, BOARD_COLOR_TRANSPARENT_B, ALPHA_COLOR_TRANSPARENT);

            if (error)
            {
                throw std::runtime_error(SDL_GetError());
            }

            // Piece texture
            error = SDL_RenderCopy(renderer_, selected_piece_->GetTexture(), nullptr, &rectangle);

            if (error)
            {
                throw std::runtime_error(SDL_GetError());
            }
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
        current_position_ = { event.button.x / POSITION_WIDTH, event.button.y / POSITION_HEIGHT };
        std::cout << "current=[" << current_position_.column<< ", " << current_position_.row << "]" << '\n';

        selected_piece_ = std::move(board_[current_position_.row][current_position_.column]);

        if (selected_piece_ != nullptr)
        {
            std::cout << "selected=[" << selected_piece_->GetPosition().column << ", " << selected_piece_->GetPosition().row << "]" << '\n';
        }
    }
}

void Game::OnMouseReleased(const SDL_Event& event)
{
    int error = 0;

    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if (selected_piece_ != nullptr)
        {
            Position new_position{ event.button.x / POSITION_WIDTH, event.button.y / POSITION_HEIGHT };
            std::cout << "new=[" << new_position.column << ", " << new_position.row << "]" << '\n';

            if (CanMove(current_position_, new_position))
            {
                // Set piece to new position
                selected_piece_->SetPosition(new_position);
                board_[new_position.row][new_position.column] = std::move(selected_piece_);
            }
            else
            {
                // Set piece to old position
                const auto old_position = selected_piece_->GetPosition();
                selected_piece_->SetPosition(new_position);
                board_[old_position.row][old_position.column] = std::move(selected_piece_);
            }

            // Play SFX
            if (Mix_PlayChannel(SOUND_PLAY_CHANNEL, move_piece_sfx_, SOUND_NO_REPEAT) == SOUND_ERROR)
            {
                throw std::runtime_error(Mix_GetError());
            }
        }
    }
}

bool Game::isRunning() const
{
    return is_running_;
}

const ChessBoard& Game::GetBoard() const
{
    return board_;
}

ChessBoard& Game::GetBoard()
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

const Position& Game::GetCurrentPosition() const
{
    return current_position_;
}

Position& Game::GetCurrentPosition()
{
    return current_position_;
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
