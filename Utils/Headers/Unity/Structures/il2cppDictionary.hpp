#pragma once

namespace Unity
{
	template<typename TKey,typename TValue>
	struct il2cppDictionary : il2cppObject
	{
		struct Entry
		{
			int m_iHashCode;
			int m_iNext;
			TKey m_tKey;
			TValue m_tValue;
		};
		il2cppArray<int>* m_pBuckets;
		il2cppArray<Entry*>* m_pEntries;
		int m_iCount;
		int m_iVersion;
		int m_iFreeList;
		int m_iFreeCount;
		void* m_pComparer;
		void* m_pKeys;
		void* m_pValues;

		Entry* GetEntry()
		{
			return (Entry*)m_pEntries->GetData();
		}

		void RemoveAll()
		{
			if (m_iCount > 0)
			{
				memset(GetEntry(), 0, sizeof(Entry*) * m_iCount);
				m_iCount = 0;
			}
		}

		void RemoveByIndex(int iIndex)
		{
			if (iIndex >= m_iCount)
				return;

			if (m_iCount > (iIndex + 1))
			{
				for (unsigned int u = iIndex; (static_cast<unsigned int>(m_iCount) - iIndex) > u; ++u)
					GetEntry()[u] = GetEntry()[u + 1];
			}

			--m_iCount;
		}

		void RemoveByKey(TKey tKey)
		{
			for (int i = 0; i < m_iCount; i++) {
				if (GetEntry()[i].m_tKey == tKey) {
					RemoveByIndex(i);
				}
			}
		}

		void Add(TKey tKey, TValue tValue)
		{
			this->GetEntry()[this->m_iCount].m_tKey = tKey;
			this->GetEntry()[this->m_iCount].m_tValue = tValue;
			this->m_iCount++;
		}

		void ReplaceByIndex(int iIndex, TKey tKey, TValue tValue)
		{
			this->GetEntry()[iIndex].m_tKey = tKey;
			this->GetEntry()[iIndex].m_tValue = tValue;
		}

		void ReplaceByKey(TKey tKey, TKey newKey, TValue tValue)
		{
			for (int i = 0; i < m_iCount; i++) {
				if (GetEntry()[i].m_tKey == tKey) {
					ReplaceByIndex(i, newKey, tValue);
				}
			}
		}

		TKey GetKeyByIndex(int iIndex)
		{
			TKey tKey = { 0 };
			
			Entry* pEntry = GetEntry();
			if (pEntry)
				tKey = pEntry[iIndex].m_tKey;

			return tKey;
		}

		TValue GetValueByIndex(int iIndex)
		{
			TValue tValue = { 0 };

			Entry* pEntry = GetEntry();
			if (pEntry)
				tValue = pEntry[iIndex].m_tValue;

			return tValue;
		}

		TValue GetValueByKey(TKey tKey)
		{
			TValue tValue = { 0 };
			for (int i = 0; i < m_iCount; i++) {
				if (GetEntry()[i].m_tKey == tKey)
					tValue =  GetEntry()[i].m_tValue;
			}
			return tValue;
		}

		void EditValue(TKey tKey, TValue newValue)
		{
			for (int i = 0; i < m_iCount; i++) {
				if (GetEntry()[i].m_tKey == tKey) {
					GetEntry()[i].m_tValue = newValue;
				}
			}
		}

		void EditKey(TKey tKey, TKey newKey)
		{
			for (int i = 0; i < m_iCount; i++) {
				if (GetEntry()[i].m_tKey == tKey) {
					GetEntry()[i].m_tKey = newKey;
				}
			}
		}

	};
}
