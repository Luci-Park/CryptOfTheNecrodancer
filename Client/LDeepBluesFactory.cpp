#include "LDeepBluesFactory.h"
#include "LBishop.h"
#include "LKing.h"
#include "LKnight.h"
#include "LPawn.h"
#include "LQueen.h"
#include "LRook.h"
#include "LObject.h"
#include "LMapManager.h"
namespace cl
{
    //King, Queen, rook, bishops, knights, pawn
    TileObject* cl::DeepBluesFactory::CreateBoss(Vector2 index, Scene* scene)
    {
        Vector2 idx = index + Vector2(3, 0);
        King* king = object::Instantiate<King>(scene, idx * UNITLENGTH, eLayerType::Monster);
        king->SetIndex(idx);
        king->SetInitialBeat(-7);
        MapManager::Move(king, Vector2::Zero, idx);
        
        idx = index + Vector2(4, 0);
        Queen* queen = object::Instantiate<Queen>(scene, idx * UNITLENGTH, eLayerType::Monster);
        queen->SetIndex(idx);
        queen->SetInitialBeat(-7);
        MapManager::Move(queen, Vector2::Zero, idx);
        queen->SetKing(king);
        king->AddPiece(queen);
        
        idx = index + Vector2(0, 0);
        Rook* rook1 = object::Instantiate<Rook>(scene, idx * UNITLENGTH, eLayerType::Monster);
        rook1->SetIndex(idx);
        rook1->SetInitialBeat(-7);
        MapManager::Move(rook1, Vector2::Zero, idx);
        rook1->SetKing(king);
        king->AddPiece(rook1);
        
        idx = index + Vector2(7, 0);
        Rook* rook2 = object::Instantiate<Rook>(scene, idx * UNITLENGTH, eLayerType::Monster);
        rook2->SetIndex(idx);
        rook2->SetInitialBeat(-7);
        MapManager::Move(rook2, Vector2::Zero, idx);
        rook2->SetKing(king);
        king->AddPiece(rook2);

        idx = index + Vector2(2, 0);
        Bishop* bishop1 = object::Instantiate<Bishop>(scene, idx * UNITLENGTH, eLayerType::Monster);
        bishop1->SetIndex(idx);
        bishop1->SetInitialBeat(-3);
        MapManager::Move(bishop1, Vector2::Zero, idx);
        bishop1->SetKing(king);
        king->AddPiece(bishop1);

        idx = index + Vector2(5, 0);
        Bishop* bishop2 = object::Instantiate<Bishop>(scene, idx * UNITLENGTH, eLayerType::Monster);
        bishop2->SetIndex(idx);
        bishop2->SetInitialBeat(-4);
        MapManager::Move(bishop2, Vector2::Zero, idx);
        bishop2->SetKing(king);
        king->AddPiece(bishop2);

        idx = index + Vector2(1, 0);
        Knight* knight1 = object::Instantiate<Knight>(scene, idx * UNITLENGTH, eLayerType::Monster);
        knight1->SetIndex(idx);
        MapManager::Move(knight1, Vector2::Zero, idx);
        knight1->SetKing(king);
        king->AddPiece(knight1);

        idx = index + Vector2(6, 0);
        Knight* knight2 = object::Instantiate<Knight>(scene, idx * UNITLENGTH, eLayerType::Monster);
        knight2->SetIndex(idx);
        MapManager::Move(knight2, Vector2::Zero, idx);
        knight2->SetKing(king);
        king->AddPiece(knight2);

        bool isKnightOpening = GetRandomInt(1, 8) == 1;
        bool knightOrder = GetRandomInt(0, 1);
        int pawnDirection = GetRandomInt(0, 1) ? -1 : 1;
        int initialPawn = GetRandomInt(0, 7);

        if (knightOrder)
        {
            knight1->SetInitialBeat(-3);
            knight2->SetInitialBeat(-5);
        }
        else {
            knight1->SetInitialBeat(-5);
            knight2->SetInitialBeat(-3);
        }
        
        if (isKnightOpening)
        {
            if (knightOrder)
                knight1->SetInitialBeat(0);
            else
                knight2->SetInitialBeat(0);
        }
        for (int i = 0; i < 8; ++i)
        {
            idx = index + Vector2((7 + initialPawn + i * pawnDirection) % 8, 1);
            Pawn* pawn = object::Instantiate<Pawn>(scene, idx * UNITLENGTH, eLayerType::Monster);
            pawn->SetIndex(idx);
            pawn->SetInitialBeat(-i - isKnightOpening - 1);
            MapManager::Move(pawn, Vector2::Zero, idx);
            pawn->SetKing(king);
            king->AddPiece(pawn);
        }
      return rook1;
    }
}
