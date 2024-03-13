using LunikEditor.Components;
using LunikEditor.EngineAPIStructs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LunikEditor.EngineAPIStructs
{
    [StructLayout(LayoutKind.Sequential)]
    class TransformComponent
    {
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale = new Vector3(1, 1, 1);
    }

    [StructLayout(LayoutKind.Sequential)]
    class GameEntityDescriptor
    {
        public TransformComponent Transform = new TransformComponent();
    }
}
namespace LunikEditor.DLLWrapper
{
    static class EngineAPI
    {
        private const string _DLLName = "EngineDLL.dll";

        [DllImport(_DLLName)]
        private static extern int CreateGameEntity(GameEntityDescriptor desc);

        public static int CreateGameEntity(GameEntity entity)
        {
            GameEntityDescriptor desc = new GameEntityDescriptor();

            // Transform
            {
                var c = entity.GetComponent<Transform>();
                desc.Transform.position = c.Location;
                desc.Transform.rotation = c.Rotation;
                desc.Transform.scale = c.Scale;
            }

            return CreateGameEntity(desc);
        }

        [DllImport(_DLLName)]
        private static extern void RemoveGameEntity(int id);

        public static void RemoveGameEntity(GameEntity entity)
        {
            RemoveGameEntity(entity.EntityID);
        }
    }
}
