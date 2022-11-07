using UnityEngine;
using UnityPraktika.P0.Scripts.VectorVisualization.Core;

namespace UnityPraktika.P0.Scripts.VectorVisualization
{
    public class VectorScalarMultiply : VectorCalculate
    {
        [Header("Values")]
        [SerializeField] private Vector3 _vectorToMultiply;
        [SerializeField] private float _by = 1;

        protected override void DrawGizmos()
        {
            DrawVectorWithArrowHead(Vector3.zero, _vectorToMultiply * _by, Color.red);
            DrawVectorWithArrowHead(Vector3.zero, _vectorToMultiply, Color.blue);
        }
    }
}