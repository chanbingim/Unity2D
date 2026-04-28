using UnityEngine;

namespace InputCommand
{
    public interface ICommand
    {
   
    }

    public abstract class CBaseCommand : ICommand
    {
     
    }

    class CMoveCommand : CBaseCommand
    {
        public Vector3      m_vCurPos;
        public Vector3      m_vDir;
        public float        m_fSpeed;

        public CMoveCommand(Vector3 Pos, Vector3 Dir, float Speed)
        {
            m_vCurPos = Pos;
            m_vDir = Dir;
            m_fSpeed = Speed;
        }
    }

    class CATK_Command : CBaseCommand
    {
        public float    m_fATK_Damage;
        public float    m_fATK_Speed;

        public CATK_Command(float damage, float Speed)
        {
            m_fATK_Damage = damage;
            m_fATK_Speed = Speed;
        }
    }
}
