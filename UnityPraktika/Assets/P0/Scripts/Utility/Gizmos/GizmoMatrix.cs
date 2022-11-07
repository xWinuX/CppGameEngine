using System;
using UnityEngine;

namespace UnityPraktika.P0.Scripts.Utility.Gizmos
{
    public readonly struct GizmoMatrix : IDisposable
    {
        private readonly Matrix4x4 _previousMatrix;

        public GizmoMatrix(Matrix4x4 matrix)
        {
            _previousMatrix           = UnityEngine.Gizmos.matrix;
            UnityEngine.Gizmos.matrix = matrix;
        }

        public void Dispose() { UnityEngine.Gizmos.matrix = _previousMatrix; }
    }
}