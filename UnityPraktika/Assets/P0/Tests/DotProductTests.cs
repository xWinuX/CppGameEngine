using NUnit.Framework;
using P0.Tests.Utility;
using UnityEngine;

namespace P0.Tests
{
    public class DotProductTests
    {
        [Test]
        public void DotProduct_Of_Two_Normalized_Vectors_Should_Be_Normalized_With_Static_Vectors()
        {
            Vector3 a = new Vector3(12f, -4f, 4.3f);
            Vector3 b = new Vector3(-2f, 0f, -0.3f);
            
            AssertUtility.AssertNormalized(VectorUtility.GetDotProductOfVectorsNormalized(a, b));
        }

        [Test]
        public void DotProduct_Of_Two_Normalized_Vectors_Should_Be_Normalized_With_Random_Vectors()
        {
            for (int i = 0; i < 10; i++)
            {
                Vector3 a = VectorUtility.GetRandomVector();
                Vector3 b = VectorUtility.GetRandomVector();
                
                AssertUtility.AssertNormalized(VectorUtility.GetDotProductOfVectorsNormalized(a, b));
            }
        }

        [Test]
        public void DotProduct_Of_Two_Normalized_Vectors_Should_Be_Normalized_With_One_Zero_Vector()
        {
            Vector3 a = Vector3.zero;
            Vector3 b = new Vector3(-2f, 0f, -0.3f);
            
            AssertUtility.AssertNormalized(VectorUtility.GetDotProductOfVectorsNormalized(a, b));
        }
        
        [Test]
        public void DotProduct_Of_Two_Normalized_Vectors_Should_Be_Normalized_With_Two_Zero_Vectors()
        {
            Vector3 a = Vector3.zero;
            Vector3 b = Vector3.zero;
            
            AssertUtility.AssertNormalized(VectorUtility.GetDotProductOfVectorsNormalized(a, b));
        }
    }
}
