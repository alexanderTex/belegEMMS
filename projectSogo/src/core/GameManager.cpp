#include "GameManager.h"

void GameManager::ComputeTurn()
{
    if(m_data->GetCurrentPlayer()->GetType() == Player::Ai)
    {
        Vector3 choice;
        MiniMax(m_data->GetField(), m_data->GetCurrentPlayer()->GetColor(), m_data->GetCurrentPlayer()->GetColor(), 4, &choice);

        m_data->MakeMove(choice);
    }
}
