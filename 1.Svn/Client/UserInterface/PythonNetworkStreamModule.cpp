///Add
#if defined(__LOADING_TIP__)
#include "LTiplist.h"
#include "PythonBackground.h"
PyObject* netGetTipInfo(PyObject* poSelf, PyObject* poArgs)
{
	std::string Find("Normal");
	if (!NS_TipList::Tip_List.empty()) {
		const auto it = std::find_if(NS_TipList::Tip_List.begin(), NS_TipList::Tip_List.end(), [](const std::pair<std::string, std::pair<std::vector<int>, std::vector<long>>>& t) {return (std::find(std::get<NS_TipList::MAP_VEC>(t.second).begin(), std::get<NS_TipList::MAP_VEC>(t.second).end(), CPythonBackground::Instance().GetWarpMapIndex()) != std::get<NS_TipList::MAP_VEC>(t.second).end()); });
		if (it != NS_TipList::Tip_List.end())
			Find = it->first;

		try {
			const auto& VnumVec = std::get<NS_TipList::VNUM_VEC>(NS_TipList::Tip_List.at(Find));
			const auto& idx = VnumVec.at(random_range(0, VnumVec.size() - 1));
			Find = CPythonNetworkStream::Instance().GetTipMap().at(idx);
		}		
		catch (const std::out_of_range& ex) {
			TraceError("netGetTipInfo error:: %s", ex.what());
			TraceError("netGetTipInfo---> Find:%s ", Find.c_str());
		}
	}

	return Py_BuildValue("s", Find.c_str());
}
#endif

//Find
		{ "GetServerInfo",						netGetServerInfo,						METH_VARARGS },
		
///Add
#if defined(__LOADING_TIP__)
		{ "GetTipInfo",							netGetTipInfo,							METH_VARARGS },
#endif
