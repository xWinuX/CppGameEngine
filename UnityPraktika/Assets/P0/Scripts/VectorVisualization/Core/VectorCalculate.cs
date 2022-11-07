using UnityEngine;
using UnityPraktika.P0.Scripts.Utility.Gizmos;

namespace UnityPraktika.P0.Scripts.VectorVisualization.Core
{
    public abstract class VectorCalculate : MonoBehaviour
    {
        [Header("Visualization")]
        [SerializeField] private float _arrowHeadLength = 0.2f;
        [SerializeField] private float _arrowHeadRadius = 0.2f;

        protected void DrawVectorWithArrowHead(Vector3 position, Vector3 vector, Color color)
        {
            GizmosUtility.DrawVectorWithArrowHead(position, vector, color, _arrowHeadRadius, _arrowHeadLength);
        }

        protected abstract void DrawGizmos();

        private void DrawGizmosLocally()
        {
            using (new GizmoMatrix(transform.localToWorldMatrix)) { DrawGizmos(); }
        }

        private void OnDrawGizmos() { DrawGizmosLocally(); }
    }
}