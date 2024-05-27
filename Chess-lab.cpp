#include <iostream>
#include <vector>
#include <string>

const int doska_SIZE = 8;

// Фигуры

enum Piece {
    ROOK,
    PAWN,
    BISHOP,
    QUEEN,
    KING,
    KNIGHT
};

// Возвращает матрицу (доску)

std::vector<std::vector<int>> olddoska() {
    return std::vector<std::vector<int>>(doska_SIZE, std::vector<int>(doska_SIZE, 0));
}


// Проверяет нахождение фигуры на доске в целом

bool figura_na_doske(int x, int y) {
    return x >= 0 && x < doska_SIZE && y >= 0 && y < doska_SIZE;
}

// Ходы для ладьи

std::vector<std::vector<int>> rook_moves(int x, int y) {
    std::vector<std::vector<int>> doska = olddoska();
    for (int i = 0; i < doska_SIZE; ++i) {
        if (i != x) doska[i][y] = 1;
        if (i != y) doska[x][i] = 1;
    }
    doska[x][y] = 2;
    return doska;
}

// Ходы для пешки

std::vector<std::vector<int>> pawn_moves(int x, int y, bool  belaya) {
    std::vector<std::vector<int>> doska = olddoska();
    int napravlenie =  belaya ? -1 : 1;
    if (figura_na_doske(x + napravlenie, y)) doska[x + napravlenie][y] = 1;
    doska[x][y] = 2;
    return doska;
}


// Ходы для слона

std::vector<std::vector<int>> bishop_moves(int x, int y) {
    std::vector<std::vector<int>> doska = olddoska();
    for (int i = 1; i < doska_SIZE; ++i) {
        if (figura_na_doske(x + i, y + i)) doska[x + i][y + i] = 1;
        if (figura_na_doske(x + i, y - i)) doska[x + i][y - i] = 1;
        if (figura_na_doske(x - i, y + i)) doska[x - i][y + i] = 1;
        if (figura_na_doske(x - i, y - i)) doska[x - i][y - i] = 1;
    }
    doska[x][y] = 2;
    return doska;
}

// Ходы для королевы

std::vector<std::vector<int>> queen_moves(int x, int y) {
    std::vector<std::vector<int>> doska = rook_moves(x, y);
    std::vector<std::vector<int>> bishopMoves = bishop_moves(x, y);
    for (int i = 0; i < doska_SIZE; ++i) {
        for (int j = 0; j < doska_SIZE; ++j) {
            if (bishopMoves[i][j] == 1) doska[i][j] = 1;
        }
    }
    doska[x][y] = 2;
    return doska;
}


// Ходы для короля

std::vector<std::vector<int>> king_moves(int x, int y) {
    std::vector<std::vector<int>> doska = olddoska();
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (figura_na_doske(x + i, y + j) && !(i == 0 && j == 0)) {
                doska[x + i][y + j] = 1;
            }
        }
    }
    doska[x][y] = 2;
    return doska;
}

// Ходы для коня

std::vector<std::vector<int>> knight_moves(int x, int y) {
    std::vector<std::vector<int>> doska = olddoska();
    int dx[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    for (int i = 0; i < 8; ++i) {
        if (figura_na_doske(x + dx[i], y + dy[i])) {
            doska[x + dx[i]][y + dy[i]] = 1;
        }
    }
    doska[x][y] = 2;
    return doska;
}

// Вывод доски на экран

void newdoska(const std::vector<std::vector<int>>& doska) {
    for (const auto& row : doska) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

// Кейсы

std::vector<std::vector<int>> ready_moves(Piece piece, int x, int y, bool  belaya = true) {
    switch (piece) {
    case ROOK: return rook_moves(x, y);
    case PAWN: return pawn_moves(x, y,  belaya);
    case BISHOP: return bishop_moves(x, y);
    case QUEEN: return queen_moves(x, y);
    case KING: return king_moves(x, y);
    case KNIGHT: return knight_moves(x, y);
    default: return olddoska();
    }
}



// НИЖЕ НАДО МЕНЯТЬ КООРДИНАТЫ И НАЗВАНИЕ ФИГУРЫ ДЛЯ СООТВЕТСТВУЮЩЕГО ВЫВОДА. ПРИВЕДЁН ПРИМЕР ДЛЯ ЛАДЬИ



int main() {
    int x = 3, y = 5;
    Piece piece = ROOK;

    std::vector<std::vector<int>> availableMoves = ready_moves(piece, x, y);
    newdoska(availableMoves);

    return 0;
}
