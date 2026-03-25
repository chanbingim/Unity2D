using UnityEngine;

[ExecuteAlways]
// 에디터에서 매번 실행 될 수 있게 설정
public class InstancingModel : MonoBehaviour
{
    public Mesh mesh;
    public Material material; // GPU Instancing 체크 필수

    [ContextMenuItem("Reset Value", "ResetValue")]
    [SerializeField] private int COUNT = 1000;
    [SerializeField] private int radius = 30; // 생성할때 나올 반경을 표시

    //DX랑 다를게 없다 그냥 만들고 싶은 개수만큼 행렬만들고 넘겨주면된다.
    private Matrix4x4[] m_Intance_matrix;
    private bool m_bIsGenrated = false;
    private int m_iDrawCount = 1000;

    void Start()
    {
       
    }

    void Update()
    {
        if (null == mesh || null == material || null == m_Intance_matrix || !m_bIsGenrated)
            return;

        // 최대 1023개씩 분할 호출
        Graphics.DrawMeshInstanced(mesh, 0, material, m_Intance_matrix, m_iDrawCount);
    }

    [ContextMenu("Generate")]
    public void Generate()
    {
        m_Intance_matrix = new Matrix4x4[COUNT];
        for (int i = 0; i < COUNT; i++)
        {
            float angle = i * Mathf.PI * 2f / COUNT;
            Vector3 pos = new Vector3(Mathf.Cos(angle), 0, Mathf.Sin(angle)) * Random.Range(radius, radius * radius);

            Quaternion rot = Quaternion.identity;
            Vector3 scl = Vector3.one * Random.Range(0.5f, 1.0f);

            // TRS 행렬 생성 (Translation · Rotation · Scale)
            m_Intance_matrix[i] = Matrix4x4.TRS(pos, rot, scl);
        }

        m_iDrawCount = COUNT;
        m_bIsGenrated = true;
    }

}
