using UnityEngine;
using UnityPraktika.P0.Scripts.Utility.Gizmos;
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
            // Draw vectors
            DrawVectorWithArrowHead(Vector3.zero, _a, Color.blue);
            DrawVectorWithArrowHead(Vector3.zero, _b, Color.yellow);
            
            // Draw cross product
            DrawVectorWithArrowHead(Vector3.zero, Vector3.Cross(_a, _b), Color.red);
            
            // Draw rectangle helper lines 
            GizmosUtility.DrawVector(_b, _a, Color.blue);
            GizmosUtility.DrawVector(_a, _b, Color.yellow);
        }
    }
}