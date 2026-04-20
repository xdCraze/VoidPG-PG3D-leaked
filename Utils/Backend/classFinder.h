#include "patterns.h"


void INIT_CLASSES() {
	BNM::Image* flkwjkfoegkoewdkseesfseg = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
	BNM::Image* saödfsedlfdasefksedrfgse = BNM::Domain().Assembly(OBF("mscorlib"))->Image();

	REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("WeaponManager")), ___skibidi::______aa__);
	REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("ExperienceController")), ___skibidi::______aa____);

	size_t classCount = il2cpp_image_get_class_count(CommonLibImages::AssemblyCSharp);
	for (int j = 0; j < classCount; j++) {
		Il2CppClass* klass = const_cast<Il2CppClass*>(il2cpp_image_get_class(CommonLibImages::AssemblyCSharp, j));

			if (NAMESPACE_CHECK(klass, OBF("BestHTTP.SocketIO"))) {
				REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("BestHTTP.SocketIO.Packet")), ___skibidi::______aa_____);
				continue;
			}

			if (NAMESPACE_CHECK(klass, OBF("Rilisoft.WebSocket"))) {
				REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("Rilisoft.WebSocket.WebSocketManager")), ___skibidi::______aa___);
				continue;
			}

			if (NAMESPACE_CHECK(klass, "")) {

				if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::dojkfoekfgjuirjfgrue)) {
					REG_CLASS(klass, ___skibidi::______bb____);
					continue;
				}

			}

			if (NAMESPACE_CHECK(klass, OBF("PGCompany"))) {

				if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::ofkeofkerigsiefsee)) {
					REG_CLASS(klass, ___skibidi::______aa);
					continue;
				}

				if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::wdwefgssedfsegsdrh)) {
					REG_CLASS(klass, ___skibidi::_____aa);
					continue;
				}

			}

			if (NAMESPACE_CHECK(klass, OBF("Rilisoft"))) {

				if (Il2CppUtils::ClassPatternCheck(klass, 1, 3, { OBF("SymmetricAlgorithm") })) {
					REG_CLASS(klass, ___skibidi::______aa______);
					continue;
				}

			}

			if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::isdoefgijefjefdmegeg)) {
				REG_CLASS(klass, ___skibidi::____aa);
				continue;
			}

			if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::isdoefgijefjefdmegag)) {
				REG_CLASS(klass, ___skibidi::___aa);
				continue;
			}

			if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::wikfneifefeufjudjefj)) {
				REG_CLASS(klass, ___skibidi::___aa_);
				continue;
			}

			if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::wedfwfergjnefgjkenmg)) {
				REG_CLASS(klass, ___skibidi::___aa___);
				continue;
			}

			if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::ihuierhgjrgsdmbnfnef)) {
				REG_CLASS(klass, ___skibidi::AnalyticsController);
				continue;
			}

			if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::sedfefkjenfjedfjeewe)) {
				REG_CLASS(klass, ___skibidi::PlayerMoveCList);
				continue;
			}
	}
}
/*
void LoadClasses(Il2CppClass* klass, const Il2CppImage* image, int classNumber = 0) {

    BNM::Image* flkwjkfoegkoewdkseesfseg = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
    BNM::Image* saödfsedlfdasefksedrfgse = BNM::Domain().Assembly(OBF("mscorlib"))->Image();

    if (image == CommonLibImages::AssemblyCSharp) {

        if (NAMESPACE_CHECK(klass, OBF("BestHTTP.SocketIO"))) {
            REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("BestHTTP.SocketIO.Packet")), ___skibidi::______aa_____);
        }

        if (NAMESPACE_CHECK(klass, OBF("Rilisoft.WebSocket"))) {
            REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("Rilisoft.WebSocket.WebSocketManager")), ___skibidi::______aa___);
        }

        if (NAMESPACE_CHECK(klass, "")) {

            REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("WeaponManager")), ___skibidi::______aa__);
            REG_CLASS((Il2CppClass*)flkwjkfoegkoewdkseesfseg->Class(OBF("ExperienceController")), ___skibidi::______aa____);

            if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::dojkfoekfgjuirjfgrue)) {
                REG_CLASS(klass, ___skibidi::______bb____);
            }

        }

        if (NAMESPACE_CHECK(klass, OBF("PGCompany"))) {

            if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::ofkeofkerigsiefsee)) {
                REG_CLASS(klass, ___skibidi::______aa);
            }

            if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::wdwefgssedfsegsdrh)) {
                REG_CLASS(klass, ___skibidi::_____aa);
            }

        }

        if (NAMESPACE_CHECK(klass, OBF("Rilisoft"))) {

            if (Il2CppUtils::ClassPatternCheck(klass, 1, 3, { OBF("SymmetricAlgorithm") })) {
                REG_CLASS(klass, ___skibidi::______aa______);
            }

        }

    }

    if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::isdoefgijefjefdmegeg)) {
        REG_CLASS(klass, ___skibidi::____aa);
    }

    if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::isdoefgijefjefdmegag)) {
        REG_CLASS(klass, ___skibidi::___aa);
    }

    if (Il2CppUtils::CheckFieldPatternV2(klass, _skibidi::wikfneifefeufjudjefj)) {
        REG_CLASS(klass, ___skibidi::___aa_);
    }

    if (Il2CppUtils::CheckFieldPatternV3(klass, _skibidi::wedfwfergjnefgjkenmg)) {
        REG_CLASS(klass, ___skibidi::___aa___);
    }
}
*/