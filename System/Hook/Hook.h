#pragma once

#include "../../stdafx.h"

#define vpnter(ptr) (((unsigned long long)ptr < 0x7FFFFFFEFFFF && (unsigned long long)ptr > 0x00010000))

class vmt {

private:

	auto GetVtableSize(uint64_t class_member)->SIZE_T;

public:

	auto ShadowHookObject(uint64_t Object, void* HookFunction, void** HookOrig, DWORD Index)-> bool;

};

#if 0
namespace Hook
{
    class NewHook
    {
    public:
        template <typename Type>
        bool VMT(void* Address, void* Function, int Index, Type* Original)
        {
            this->OriginalVTable = *(uintptr_t**)(Address);

            if (this->LastHookedFunctionAddress && this->LastHookedFunctionIndex)
            {
                if (this->LastHookedFunctionAddress == this->OriginalVTable[this->LastHookedFunctionIndex])
                {
                    return false;
                }
            }

            Type OriginalFunction = reinterpret_cast<Type>(this->OriginalVTable[Index]);
            if (OriginalFunction != Function)
            {
                int i = 0;
                for (;; i++)
                {
                    void* VirtualFunction = (void*)this->OriginalVTable[i];
                    if (!VirtualFunction)
                        break;

                    this->VTableSize++;
                }

                if (Index < this->VTableSize)
                {
                    uintptr_t* AllocatedVTable = reinterpret_cast<uintptr_t*>(LI_FN(calloc).safe_cached()(this->VTableSize * sizeof(uintptr_t), 0x10));

                    for (int i = 0; i < this->VTableSize; i++)
                    {
                        AllocatedVTable[i] = this->OriginalVTable[i];
                    }

                    *Original = OriginalFunction;

                    AllocatedVTable[Index] = reinterpret_cast<uintptr_t>(Function);

                    *(uintptr_t**)(Address) = AllocatedVTable;

                    this->LastHookedFunctionAddress = reinterpret_cast<uintptr_t>(Function);
                    this->LastHookedFunctionIndex = Index;

                    return true;
                }
            }

            return false;
        }

        template <typename Type>
        void RevertHook(Type* Original, void* Address)
        {
            if (this->OriginalVTable && this->LastHookedFunctionIndex)
            {
                uintptr_t* VirtualTable = *(uintptr_t**)(Address);

                VirtualTable[this->LastHookedFunctionIndex] = reinterpret_cast<uintptr_t>(*Original);

                *(uintptr_t**)Address = this->OriginalVTable;

                //FMemory::Free(VirtualTable);
                LI_FN(free).safe_cached()(VirtualTable);

                this->LastHookedFunctionAddress = 0x0;
                this->LastHookedFunctionIndex = -1;
            }
        }

    private:
        uintptr_t* OriginalVTable;
        uintptr_t LastHookedFunctionAddress;
        int LastHookedFunctionIndex;
        int VTableSize = 0;
    };
}
#endif
#if 0
namespace Hook
{
    class ShadowVMT {
    public:

        ShadowVMT()
        {

        }

        ShadowVMT(void* VTable)
        {
            this->Address = VTable;

            this->OriginalVTable = *(void***)this->Address;

            this->VTableSize = 0;

            int i = 0;
            for (;; i++)
            {
                void* VirtualFunction = (void*)this->OriginalVTable[i];

                if (!VirtualFunction)
                    break;

                this->VTableSize++;
            }
        }

        template <typename T>
        T Hook(int Index, void* HookFunction)
        {
            void* OriginalFunction = (void*)this->OriginalVTable[Index];

            //this->FakeVTable = reinterpret_cast<void**>(SpoofCaller<void*>(Malloc, this->VTableSize * 8, 0x10));
            this->FakeVTable = reinterpret_cast<void**>(LI_FN(calloc).safe_cached()(this->VTableSize * 8, 0x10));

            for (int i = 0; i < this->VTableSize; i++)
            {
                if (i == Index)
                    continue;

                this->FakeVTable[i] = this->OriginalVTable[i];
            }

            this->FakeVTable[Index] = HookFunction;

            *(void**)this->Address = this->FakeVTable;

            return (T)OriginalFunction;
        }

        bool Initialize(void* VTable)
        {
            if (!VTable)
                return false;

            this->Address = VTable;

            this->OriginalVTable = *(void***)this->Address;

            if (this->LastAddress && this->LastIndex)
            {
                if (this->LastAddress == this->OriginalVTable[this->LastIndex])
                    return false;
            }

            this->VTableSize = 0;

            int i = 0;
            for (;; i++)
            {
                void* VirtualFunction = (void*)this->OriginalVTable[i];

                if (!VirtualFunction)
                    break;

                this->VTableSize++;
            }

            //this->FakeVTable = reinterpret_cast<void**>(SpoofCaller<void*>(Malloc, this->VTableSize * 8, 0x10));
            this->FakeVTable = reinterpret_cast<void**>(LI_FN(calloc).safe_cached()(this->VTableSize * 8, 0x10));
            //this->FakeVTable = reinterpret_cast<void**>((void*)LI_FN(malloc).safe_cached()(this->VTableSize * 8));

            for (int i = 0; i < this->VTableSize; i++)
            {
                this->FakeVTable[i] = this->OriginalVTable[i];
            }

            return true;
        }

        template <typename T>
        T Insert(int Index, void* HookFunction)
        {
            void* OriginalFunction = (void*)this->OriginalVTable[Index];

            this->FakeVTable[Index] = HookFunction;

            this->LastAddress = HookFunction;
            this->LastIndex = Index;

            return (T)OriginalFunction;
        }

        void Finalize()
        {
            *(void**)this->Address = this->FakeVTable;
        }

        operator bool() { return bool(this->Address); }

    private:
        void* Address;
        void** OriginalVTable;
        void** FakeVTable;
        int VTableSize;

        void* LastAddress;
        int LastIndex;
    };
}
#endif