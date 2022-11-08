using UnityEngine;

namespace P0.Tests.Utility
{
    public static class VectorUtility
    {
        public static Vector3 GetRandomVector() => Random.insideUnitSphere;

        public static float GetDotProductOfVectorsNormalized(Vector3 a, Vector3 b) => Vector3.Dot(a.normalized, b.normalized);

        public static float GetAreaOfRectangleBetweenTwoVectors(Vector3 a, Vector3 b)
        {
            float angle = Vector3.Angle(a, b);
            return a.magnitude * b.magnitude * Mathf.Sin(angle * Mathf.Deg2Rad);
        }
    }
}