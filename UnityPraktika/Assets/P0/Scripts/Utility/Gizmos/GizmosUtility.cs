using UnityEngine;

namespace UnityPraktika.P0.Scripts.Utility.Gizmos
{
    public static class GizmosUtility
    {
        public static void DrawVector(Vector3 position, Vector3 vector, Color color)
        {
            using (new GizmoColor(color)) { UnityEngine.Gizmos.DrawLine(position, position + vector); }
        }

        public static void DrawVector(Vector3 position, Vector3 unitVector, float length, Color color) { DrawVector(position, unitVector * length, color); }
        
        public static void DrawVectorWithArrowHead(Vector3 position, Vector3 vector, Color color, float arrowHeadRadius = 1f, float arrowHeadLength = 1)
        {
            Vector3 direction = ((position + vector) - position).normalized;
            DrawVector(position, vector, color);
            DrawArrowHead(position + vector, direction, color, arrowHeadRadius, arrowHeadLength);
        }
        
        public static void DrawVectorWithArrowHead(Vector3 position, Vector3 unitVector, float length, Color color, float arrowHeadRadius = 1f, float arrowHeadLength = 1)
        {
            DrawVectorWithArrowHead(position, unitVector * length, color, arrowHeadRadius, arrowHeadLength);
        }
        
        /// <summary>
        /// Draws a 4 sided Arrow head
        /// </summary>
        /// <param name="position">Origin of all 4 lines</param>
        /// <param name="direction">Direction arrow head is pointing to</param>
        /// <param name="color">Color of the arrow head</param>
        /// <param name="radius">Angle at which the lines are seperated from the direction</param>
        /// <param name="length">Length of the 4 arrow head lines</param>
        public static void DrawArrowHead(Vector3 position, Vector3 direction, Color color, float radius = 10f, float length = 1f)
        {
            // Calculate rotations and angles
            Quaternion lookRotation  = Quaternion.LookRotation(direction);

            // Calculate arrow head ends
            Vector3 back  = lookRotation * new Vector3(0, 0, -length);
            Vector3 up    = lookRotation * new Vector3(0, radius, 0);
            Vector3 right = lookRotation * new Vector3(radius, 0, 0);

            // Actually draw the gizmos
            using (new GizmoColor(color))
            {
                UnityEngine.Gizmos.DrawRay(position, right + back);
                UnityEngine.Gizmos.DrawRay(position, -right + back);
                UnityEngine.Gizmos.DrawRay(position, up + back);
                UnityEngine.Gizmos.DrawRay(position, -up + back);
            }
        }
    }
}