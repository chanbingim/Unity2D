using JetBrains.Annotations;
using UnityEngine;

namespace InputCommand
{
    public interface ICommand
    {
        public void Execute();
    }

    struct CMoveCommand : ICommand
    {
        public Transform    m_Transform;
        public Vector3      m_vDir;
        public float        m_fSpeed;

        public CMoveCommand(Transform transform, Vector3 Dir, float Speed)
        {
            m_Transform = transform;
            m_vDir = Dir;
            m_fSpeed = Speed;
        }

        public void Execute() { }
    }
}
