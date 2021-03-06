#pragma once

#include "../CLinkList.h"

class CAnimBlendAssociation;
class CAnimBlendHierarchy;
class CAnimBlock;
class CAnimBlendAssocGroup;

class CAnimManager
{
    struct AnimAssocDefinition;
    struct AnimDescriptor;
public:
	static AnimAssocDefinition *AddAnimAssocDefinition(char const *group, char const *file, unsigned int type, unsigned int count, AnimDescriptor *descriptor);
	static void AddAnimBlockRef(int index);
	static void AddAnimToAssocDefinition(AnimAssocDefinition *pDef, char const *name);
    static CAnimBlendAssociation *AddAnimation(RpClump *pClump, AssocGroupId groupId, AnimationId animId); // TODO
	//* AddAnimation(RpClump*, CAnimBlendHierarchy*, int)
	static void AddAnimationAndSync(RpClump *pClump, CAnimBlendAssociation *pAnimBlendAssoc, AssocGroupId groupId, AnimationId animId);
	static void BlendAnimation(RpClump *pClump, AssocGroupId groupId, AnimationId animId, float fBlendDelta);
	static void BlendAnimation(RpClump *pClump, CAnimBlendHierarchy *pAnimHierarchy, int uiFlags, float fBlendDelta);
	static void CreateAnimAssocGroups();
	static CAnimBlendAssociation *CreateAnimAssociation(AssocGroupId group, AnimationId anim);
	static CAnimBlendAssociation *GetAnimAssociation(AssocGroupId group, AnimationId anim);
	static CAnimBlendAssociation *GetAnimAssociation(AssocGroupId group, char const *name);
	static const char *GetAnimBlockName(AssocGroupId index);
	static AnimAssocDefinition *GetAnimGroupName(AssocGroupId index);
	static CAnimBlendHierarchy *GetAnimation(char const *name, const CAnimBlock* pAnimBlock);
	static CAnimBlendHierarchy *GetAnimation(unsigned int hash, const CAnimBlock* pAnimBlock);
	static CAnimBlock *GetAnimationBlock(char const *name);
	static int32_t GetAnimationBlockIndex(char const *name);
	static AssocGroupId GetFirstAssocGroup(char const *block_name);
	static uint16_t GetNumRefsToAnimBlock(int index);
	//* Initialise()
    static void LoadAnimFileStream(RwStream* stream, char loadCompressed, const char uncompressedAnims[8][32]);
	//* LoadAnimFile(char const*)
	//* LoadAnimFiles()
	//* ReadAnimAssociationDefinitions() // read animgrp.dat
	static int32_t RegisterAnimBlock(char const *block_name);
	static void RemoveAnimBlock(int index);
	static void RemoveAnimBlockRef(int index);
	static void RemoveAnimBlockRefWithoutDelete(int index);
	static void RemoveFromUncompressedCache(CAnimBlendHierarchy *pHierarchy);
	static void RemoveLastAnimFile();
	static void Shutdown();
	static void UncompressAnimation(CAnimBlendHierarchy *pHierarchy);
protected:
    void ReadANP1(RwStream* stream, bool loadCompressed, const char uncompressedAnims[8][32]);
    void ReadANP23(RwStream *stream, bool bANP3);
private:
    struct AnimDescriptor
    {
        int32_t iIDOffset;
        struct
        {
            uint32_t uiStaticAssocId;
            uint16_t usFlags;
        } AnimAssoc[1]; // variablly-sized (count=iNumAnims)
    };
    struct AnimAssocDefinition
    {   /* read from animgrp.dat + embedded inside gta_sa executable */
        /* name of animation definition group */
        char szGroupName[16];
        /* name of file in which these animations occur (minus the IFP extension) */
        char szBlockName[16]; // a.k.a. anim block name
        /* type of animations (6 - walkcycle) */
        int32_t iGroupAnimType;
        /* number of animation names in pszAnimations */
        int32_t iNumAnims;
        /* array of animation names each max. 24 chars long */
        char *pszAnimations[24];
        AnimDescriptor pDescriptor;
    };
    static AnimAssocDefinition ms_aAnimAssocDefinitions[118];
	static CAnimBlendAssocGroup ms_aAnimAssocGroups[?];
	static CAnimBlock ms_aAnimBlocks[?];
	static CAnimBlendHierarchy *ms_aAnimations;
	static CLinkList<CAnimBlendHierarchy*> ms_animCache;
	static size_t ms_numAnimAssocDefinitions;
	static size_t ms_numAnimBlocks;
	static size_t ms_numAnimations;
};