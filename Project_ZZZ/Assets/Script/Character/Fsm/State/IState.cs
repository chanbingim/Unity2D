using UnityEngine;

namespace GameFSM
{
    public interface IFSMState
    {
        public void OnEnter();
        public void OnUpdate();
        public void Exit();
    }
}