#include "../include/core/AI.h"

#include <iostream>

using namespace std;

AI::AI()
{
    //ctor
}

AI::~AI()
{
    //dtor
}


int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, SlotVector *choice) throw(out_of_range)
{


    if(CheckForWin(field, current_player))
    {
        if(current_player == max_Player)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    std::vector<SlotVector> posPosistions = GetAllPossiblePosi(field);

    if(posPosistions.size() == 0)
    {
        return 0;
    }

    std::vector<int> scores;

    for(int i = 0; i < posPosistions.size(); i++)
    {
        PlayingField posField(field);


        posField.OccupySlot(posPosistions.at(i).X, posPosistions.at(i).Y, posPosistions.at(i).Z, current_player);



        if(current_player == PlayingField::Blue)
        {
            scores.push_back(MiniMax(&posField, max_Player, PlayingField::Red, choice));
        }
        else
        {
            scores.push_back(MiniMax(&posField, max_Player, PlayingField::Blue, choice));
        }
    }




    if(current_player == max_Player)
    {
        //Max Calculation
        int best_score_index = 0;

        for(int i = 0; i < scores.size(); i++)
        {
            if(scores.at(i) > scores.at(best_score_index))
            {
                best_score_index = i;
            }
        }

        choice->X = posPosistions.at(best_score_index).X;
        choice->Y = posPosistions.at(best_score_index).Y;
        choice->Z = posPosistions.at(best_score_index).Z;

        return scores.at(best_score_index);
    }
    else
    {
        //Min Calculation

        int worst_Score_Index = 0;

        for(int i = 0; i < scores.size(); i++)
        {
            if(scores.at(i) < scores.at(worst_Score_Index))
            {
                worst_Score_Index = i;
            }
        }

        choice->X = posPosistions.at(worst_Score_Index).X;
        choice->Y = posPosistions.at(worst_Score_Index).Y;
        choice->Z = posPosistions.at(worst_Score_Index).Z;

        return scores.at(worst_Score_Index);
    }

}

int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, int depth, SlotVector *choice) throw(out_of_range)
{


    if(depth == 0 || CheckForWin(field, current_player))
    {
        if(current_player == max_Player)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    std::vector<SlotVector> posPosistions = GetAllPossiblePosi(field);

    if(posPosistions.size() == 0)
    {
        return 0;
    }

    std::vector<int> scores;

    for(int i = 0; i < posPosistions.size(); i++)
    {
        PlayingField posField(field);


        posField.OccupySlot(posPosistions.at(i).X, posPosistions.at(i).Y, posPosistions.at(i).Z, current_player);



        if(current_player == PlayingField::Blue)
        {
            scores.push_back(MiniMax(&posField, max_Player, PlayingField::Red, depth - 1, choice));
        }
        else
        {
            scores.push_back(MiniMax(&posField, max_Player, PlayingField::Blue, depth - 1, choice));
        }
    }




    if(current_player == max_Player)
    {
        //Max Calculation
        int best_score_index = 0;

        for(int i = 0; i < scores.size(); i++)
        {
            if(scores.at(i) > scores.at(best_score_index))
            {
                best_score_index = i;
            }
        }

        choice->X = posPosistions.at(best_score_index).X;
        choice->Y = posPosistions.at(best_score_index).Y;
        choice->Z = posPosistions.at(best_score_index).Z;

        return scores.at(best_score_index);
    }
    else
    {
        //Min Calculation

        int worst_Score_Index = 0;

        for(int i = 0; i < scores.size(); i++)
        {
            if(scores.at(i) < scores.at(worst_Score_Index))
            {
                worst_Score_Index = i;
            }
        }

        choice->X = posPosistions.at(worst_Score_Index).X;
        choice->Y = posPosistions.at(worst_Score_Index).Y;
        choice->Z = posPosistions.at(worst_Score_Index).Z;

        return scores.at(worst_Score_Index);
    }

}
