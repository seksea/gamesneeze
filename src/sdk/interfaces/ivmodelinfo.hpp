
class IVModelInfo {
public:
	int GetModelIndex(const char* Filename) {
		typedef int (*Fn)(void*, const char*);
		return getVirtualFunc<Fn>(this, 3)(this, Filename);
	}

	const char* GetModelName(const model_t* model) {
		typedef const char* (*Fn)(void*, const model_t*);
		return getVirtualFunc<Fn>(this, 4)(this, model);
	}
};