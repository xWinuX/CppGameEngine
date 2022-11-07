using UnityEngine;
using UnityPraktika.P0.Scripts.VectorVisualization.Core;

namespace UnityPraktika.P0.Scripts.VectorVisualization
{
    public class VectorCrossProduct : VectorCalculate
    {
        [Header("Values")]
        [SerializeField] private Vector3 _a;
        [SerializeField] private Vector3 _b;
        
        protected override void DrawGizmos()
        {
            DrawVectorWithArrowHead(Vector3.zero, _a, Color.blue);
            DrawVectorWithArrowHead(Vector3.zero, _b, Color.yellow);
            DrawVectorWithArrowHead(Vector3.zero, Vector3.Cross(_a, _b), Color.red);
        }
    }
}