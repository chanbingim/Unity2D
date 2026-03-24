using UnityEngine;
using InputCommand;

namespace GameFSM
{
    public interface IFSMState
    {
        public void OnEnter();
        public void OnUpdate(ICommand Command);
        public void Exit();
    }
}