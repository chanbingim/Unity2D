using System;
using System.Collections.Generic;
using UnityEngine;
using static Defines;

public class CObjectPool<T>
{
    // 읽기 전용 프로퍼티로 반환
    public int ActiveCount      => m_ActiveObject.Count;
    public int UnActiveCount    => m_UnActiveObject.Count;
    public int Capacity         => m_Capacity;

    // 내부 변수들
    private Queue<T>    m_UnActiveObject = new Queue<T>();
    private HashSet<T>  m_ActiveObject = new HashSet<T>();

    private Func<T>     m_CreateFunc;
    private int         m_Count;
    private int         m_Capacity;

    private RESULT Initialize(Func<T> createFunc, int poolCount)
    {
        m_CreateFunc = createFunc;
        m_Count = poolCount;
        Expand(m_Count);

        return RESULT.SUCCESS;
    }

    private void Expand(int count)
    {
        for (int i = 0; i < count; i++)
        {
            T obj = m_CreateFunc();
            m_UnActiveObject.Enqueue(obj);
        }
        m_Capacity += count;
    }

    public static CObjectPool<T> Create_Pool(Func<T> createFunc, int poolCount)
    {
        CObjectPool<T> pool = new CObjectPool<T>();

        if (RESULT.FAIL == pool.Initialize(createFunc, poolCount))
            return null;

        return pool;
    }

    public T GetObject()
    {
        if (m_UnActiveObject.Count == 0)
            Expand(m_Count);

        T obj = m_UnActiveObject.Dequeue();
        m_ActiveObject.Add(obj);
        return obj;
    }

    public void ReleaseObject(T obj)
    {
        if (!m_ActiveObject.Contains(obj))
        {
            throw new Exception("풀에 없는 객체 반환 시도");
        }

        m_ActiveObject.Remove(obj);
        m_UnActiveObject.Enqueue(obj);
    }
}
