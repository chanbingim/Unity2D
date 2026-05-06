using System;
using UnityEngine;

public abstract class InteractableComponent : MonoBehaviour
{
    virtual public void OnInteract(InteractorComponent actor) { }
}
