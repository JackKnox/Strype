﻿using System;
using Coral.Managed.Interop;

namespace Strype
{
    public abstract class Component
    {
        public Object Object { get; internal set; }
    }

    public class TagComponent : Component
    {
        public string? Tag
        {
            get { unsafe { return InternalCalls.TagComponent_GetTag(Object.ID); } }
            set { unsafe { InternalCalls.TagComponent_SetTag(Object.ID, value); } }
        }
    }

    public class ScriptComponent : Component
    {
        public NativeInstance<object> Instance
        {
            get
            {
                unsafe { return InternalCalls.ScriptComponent_GetInstance(Object.ID); }
            }
        }
    }

    public class TransformComponent : Component
    {
        public Vector2 Position
        {
            get
            {
                Vector2 result;
                unsafe { InternalCalls.TransformComponent_GetPosition(Object.ID, &result); }
                return result;
            }

            set
            {
                unsafe { InternalCalls.TransformComponent_SetPosition(Object.ID, &value); }
            }
        }

        public float Rotation
        {
            get
            {
                float result;
                unsafe { InternalCalls.TransformComponent_GetRotation(Object.ID, &result); }
                return result;
            }

            set
            {
                unsafe { InternalCalls.TransformComponent_SetRotation(Object.ID, &value); }
            }
        }

        public Vector2 Scale
        {
            get
            {
                Vector2 result;
                unsafe { InternalCalls.TransformComponent_GetScale(Object.ID, &result); }
                return result;
            }

            set
            {
                unsafe { InternalCalls.TransformComponent_SetScale(Object.ID, &value); }
            }
        }
    }

}
