using InputCommand;
using NUnit.Framework;
using UnityEngine;

namespace GameFSM
{
    public interface IFSMState
    {
        public void OnEnter();
        public void OnUpdate(Character character, ICommand Command);
        public void Exit();
    }

    public interface IFSMState<TType> : IFSMState
    {
        TType   Type { get; }
        int     IgnoreType { get; }
    }
}