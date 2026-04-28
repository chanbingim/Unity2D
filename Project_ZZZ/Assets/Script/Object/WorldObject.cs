using UnityEngine;

public abstract class WorldObject : MonoBehaviour
{
    public enum WORLD_OBJECT_TYPE {
        ENVIRONMENT,
        REWARDBOX,
        TRAP,
        NPC,
        PORTAL,
        END
    };

    [SerializeField] private WORLD_OBJECT_TYPE m_ObjectType;
    public WORLD_OBJECT_TYPE ObjectType => m_ObjectType;
}
