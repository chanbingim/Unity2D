using UnityEngine;
using InputCommand;
using Unity.IO.LowLevel.Unsafe;

namespace GameFSM
{
    public interface IFSMState
    {
        public void OnEnter();
        public void OnUpdate(ICommand Command);
        public void Exit();
    }
}