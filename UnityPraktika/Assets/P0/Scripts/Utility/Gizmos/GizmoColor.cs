using System;
using UnityEngine;

namespace UnityPraktika.P0.Scripts.Utility.Gizmos
{
    public readonly struct GizmoColor : IDisposable
    {
        private readonly Color _previousColor;

        public GizmoColor(Color color)
        {
            _previousColor           = UnityEngine.Gizmos.color;
            UnityEngine.Gizmos.color = color;
        }

        public void Dispose() { UnityEngine.Gizmos.color = _previousColor; }
    }
}