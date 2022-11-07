using UnityEngine;
using UnityPraktika.P0.Scripts.VectorVisualization.Core;

namespace UnityPraktika.P0.Scripts.VectorVisualization
{
    public class VectorAdditionAndSubtraction : VectorCalculate
    {
        [Header("Values")]
        [SerializeField] private Vector3 _a;
        [SerializeField] private Vector3 _b;
        [SerializeField] private bool    _subtract;

        protected override void DrawGizmos()
        {
            DrawVectorWithArrowHead(Vector3.zero, _a, Color.blue);
            if (!_subtract)
            {
                DrawVectorWithArrowHead(_a, _b, Color.green);
                DrawVectorWithArrowHead(Vector3.zero, _a + _b, Color.yellow);
            }
            else
            {
                DrawVectorWithArrowHead(Vector3.zero, _b, Color.green);
                DrawVectorWithArrowHead(_b, _a - _b, Color.yellow);
            }
        }
    }
}