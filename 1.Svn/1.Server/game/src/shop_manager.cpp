//Find
		if (!pItemGroup->GetValue(i, "price", shopItems[i].price))
		{
			sys_err("row(%d) of group items of group %s does not have price column", i, pNode->GetNodeName().c_str());
			return false;
		}
		
///Add
#ifdef ENABLE_RENEWAL_SHOPEX
		if (shopItems[i].price_type >= EX_MAX || shopItems[i].price_type < EX_GOLD) {
			sys_err("row(%d) of group items of group %s price_type is wrong!", i, pNode->GetNodeName().c_str());
			return false;
		}
		char getval[20];
		for (int j = 0; j < ITEM_SOCKET_MAX_NUM; j++) {
			snprintf(getval, sizeof(getval), "socket%d", j);
			if (!pItemGroup->GetValue(i, getval, shopItems[i].alSockets[j])) {
				sys_err("row(%d) stage %d of group items of group %s does not have socket column", i, j, pNode->GetNodeName().c_str());
				return false;
			}
		}
		for (int j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; j++) {
			snprintf(getval, sizeof(getval), "attr_type%d", j);
			if (!pItemGroup->GetValue(i, getval, shopItems[i].aAttr[j].bType)) {
				sys_err("row(%d) stage %d of group items of group %s does not have attr_type column", i, j, pNode->GetNodeName().c_str());
				return false;
			}
			snprintf(getval, sizeof(getval), "attr_value%d", j);
			if (!pItemGroup->GetValue(i, getval, shopItems[i].aAttr[j].sValue)) {
				sys_err("row(%d) stage %d of group items of group %s does not have attr_value column", i, j, pNode->GetNodeName().c_str());
				return false;
			}
		}
		if (pItemGroup->GetValue(i, "price_type", shopItems[i].price_type) && pItemGroup->GetValue(i, "price_vnum", shopItems[i].price_vnum) && shopItems[i].price_type == 3) {
			if (!ITEM_MANAGER::instance().GetTable(shopItems[i].price_vnum)) {
				sys_err("NOT GET ITEM PROTO %d", shopItems[i].price_vnum);
				return false;
			}
		}
#endif

//Find
	if (boost::iequals(stSort, "Asc"))
	{
		std::sort(shopItems.begin(), shopItems.end(), CompareShopItemName);
	}
	else if(boost::iequals(stSort, "Desc"))
	{
		std::sort(shopItems.rbegin(), shopItems.rend(), CompareShopItemName);
	}
	
///Add

#ifdef ENABLE_RENEWAL_SHOPEX
	else {
		std::sort(shopItems.begin(), shopItems.end(), [&stSort](const TShopItemTable& i1, const TShopItemTable& i2) {
			const auto lItem = ITEM_MANAGER::instance().GetTable(i1.vnum);
			const auto rItem = ITEM_MANAGER::instance().GetTable(i2.vnum);
			if (!stSort.compare("Vnum"))
				return i1.vnum > i2.vnum;
			else if (!stSort.compare("Price"))
				return i1.price > i2.price;
			else if (!stSort.compare("Name") && lItem && rItem)
				return strcmp(lItem->szLocaleName, rItem->szLocaleName) < 0;
			else if (!stSort.compare("Type") && lItem && rItem)
				return lItem->bType > rItem->bType;
		});
	}
#endif