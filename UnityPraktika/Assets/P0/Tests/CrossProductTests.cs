using NUnit.Framework;
using P0.Tests.Utility;
using UnityEngine;

namespace P0.Tests
{
    public class CrossProductTests
    {
        [Test]
        public void The_Magnitude_Of_The_CrossProduct_Of_Two_Vectors_Should_Be_Equal_To_The_Area_Of_A_Rectangle_Constructed_With_Random_Vectors()
        {
            for (int i = 0; i < 10; i++)
            {
                Vector3 a = VectorUtility.GetRandomVector();
                Vector3 b = VectorUtility.GetRandomVector();
                
                AssertCrossProductOfVectors(a, b);
            }
        }

        [Test]
        public void The_Magnitude_Of_The_CrossProduct_Of_Two_Vectors_Should_Be_Equal_To_The_Area_Of_A_Rectangle_Constructed_With_The_Two_Vectors()
        {
            Vector3 a = new Vector3(12f, -4f, 4.3f);
            Vector3 b = new Vector3(-2f, 0f, -0.3f);

            AssertCrossProductOfVectors(a, b);
        }

        [Test]
        public void The_Magnitude_Of_The_CrossProduct_Of_Two_Vectors_Should_Be_Equal_To_The_Area_Of_A_Rectangle_Constructed_With_One_Zero_Vector()
        {
            Vector3 a = Vector3.zero;
            Vector3 b = new Vector3(-2f, 0f, -0.3f);
            
            AssertCrossProductOfVectors(a, b);
        }
        
        [Test]
        public void The_Magnitude_Of_The_CrossProduct_Of_Two_Vectors_Should_Be_Equal_To_The_Area_Of_A_Rectangle_Constructed_With_Two_Zero_Vectors()
        {
            Vector3 a = Vector3.zero;
            Vector3 b = Vector3.zero;
            
            AssertCrossProductOfVectors(a, b);
        }
        
        
        private static void AssertCrossProductOfVectors(Vector3 a, Vector3 b)
        {
            Vector3 crossProduct = Vector3.Cross(a, b);
            
            UnityEngine.Assertions.Assert.AreApproximatelyEqual(crossProduct.magnitude, VectorUtility.GetAreaOfRectangleBetweenTwoVectors(a, b), 0.1f);
        }
    }
}