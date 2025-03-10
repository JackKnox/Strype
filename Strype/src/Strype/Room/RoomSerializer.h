#pragma once

#include "Room.h"

namespace Strype {

	class RoomSerializer
	{
	public:
		RoomSerializer(const Ref<Room>& room);

		void Serialize(const std::filesystem::path& filepath);
		void Deserialize(const std::filesystem::path& filepath);
	private:
		Ref<Room> m_Room;
	};

}