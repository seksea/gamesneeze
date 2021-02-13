#pragma once

class KeyValues;

//-----------------------------------------------------------------------------
// Shader state flags can be read from the FLAGS materialvar
// Also can be read or written to with the Set/GetMaterialVarFlags() call
// Also make sure you add/remove a string associated with each flag below to CShaderSystem::ShaderStateString in ShaderSystem.cpp
//-----------------------------------------------------------------------------
enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG					  = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE		  = (1 << 1),
	MATERIAL_VAR_NO_DRAW				  = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE	  = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR			  = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA			  = (1 << 5),
	MATERIAL_VAR_SELFILLUM				  = (1 << 6),
	MATERIAL_VAR_ADDITIVE				  = (1 << 7),
	MATERIAL_VAR_ALPHATEST				  = (1 << 8),
	MATERIAL_VAR_MULTIPASS				  = (1 << 9),
	MATERIAL_VAR_ZNEARER				  = (1 << 10),
	MATERIAL_VAR_MODEL					  = (1 << 11),
	MATERIAL_VAR_FLAT					  = (1 << 12),
	MATERIAL_VAR_NOCULL					  = (1 << 13),
	MATERIAL_VAR_NOFOG					  = (1 << 14),
	MATERIAL_VAR_IGNOREZ				  = (1 << 15),
	MATERIAL_VAR_DECAL					  = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE			  = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD				  = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE	      = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK	  = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE			  = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE				  = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS		  = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT			  = (1 << 27),
	MATERIAL_VAR_WIREFRAME                = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE     = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION  = (1 << 30),

	// NOTE: Only add flags here that either should be read from
	// .vmts or can be set directly from client code. Other, internal
	// flags should to into the flag enum in imaterialinternal.h
};

class IMaterialVar {
public:

    void SetVecValue(float x, float y, float z) {
		typedef void (*Fn)(void*, float, float, float);
		return getVirtualFunc<Fn>(this, 12)(this, x, y, z);
    }
};

class IMaterial {
public:
	virtual const char*	GetName();
	virtual const char*	GetTextureGroupName();

	IMaterialVar* FindVar(const char *varName, bool *found, bool complain = true) {
		typedef IMaterialVar* (*Fn)(void*, const char*, bool*, bool);
		return getVirtualFunc<Fn>(this, 11)(this, varName, found, complain);
	}

	void AlphaModulate(float alpha) {
		typedef void (*Fn)(void*, float);
		return getVirtualFunc<Fn>(this, 27)(this, alpha);
	}

	void ColorModulate(float r, float g, float b) {
		typedef void (*Fn)(void*, float, float, float);
		return getVirtualFunc<Fn>(this, 28)(this, r, g, b);
	}

	void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) {
		typedef void (*Fn)(void*, MaterialVarFlags_t, bool);
		return getVirtualFunc<Fn>(this, 29)(this, flag, on);
	}

	float GetAlphaModulation() {
		typedef float (*Fn)(void*);
		return getVirtualFunc<Fn>(this, 44)(this);
	}

	void GetColorModulate(float *r, float *g, float *b) {
		typedef void (*Fn)(void*, float*, float*, float*);
		return getVirtualFunc<Fn>(this, 45)(this, r, g, b);
	}
};

class IMaterialSystem {
public:
	IMaterial* CreateMaterial( const char* pMaterialName, KeyValues* pVMTKeyValues ) {
		typedef IMaterial* (*Fn)( void*, const char*, KeyValues* );
		return getVirtualFunc<Fn>( this, 83 )( this, pMaterialName, pVMTKeyValues );
	}

	IMaterial* FindMaterial( char const* pMaterialName, const char* pTextureGroupName, bool complain = true,
							 const char* pComplainPrefix = 0 ) {
		typedef IMaterial* (*Fn)( void*, char const*, const char*, bool, const char* );
		return getVirtualFunc<Fn>( this, 84 )( this, pMaterialName, pTextureGroupName, complain, pComplainPrefix );
	}

	unsigned short FirstMaterial() {
		typedef unsigned short (*Fn)( void* );
		return getVirtualFunc<Fn>( this, 86 )( this );
	}

	unsigned short NextMaterial( unsigned short h ) {
		typedef unsigned short (*Fn)( void*, unsigned short );
		return getVirtualFunc<Fn>( this, 87 )( this, h );
	}

	unsigned short InvalidMaterial() {
		typedef unsigned short (*Fn)( void* );
		return getVirtualFunc<Fn>( this, 88 )( this );
	}

	IMaterial* GetMaterial( unsigned short h ) {
		typedef IMaterial* (*Fn)( void*, unsigned short );
		return getVirtualFunc<Fn>( this, 89 )( this, h );
	}
};