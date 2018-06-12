cmake_minimum_required(VERSION 3.1)
project(worms_client)

add_executable(worms_client
				client_CapturedEventSender.cpp
				client_CapturedEventFactory.cpp
				client_TeletransportationCapturedEvent.cpp
				client_RadiocontrolledCapturedEvent.cpp
				client_ClosedConnectionCapturedEvent.cpp
				client_DynamiteCapturedEvent.cpp
				client_JumpBackwardCapturedEvent.cpp
				client_JumpForwardCapturedEvent.cpp
				client_StopMovingCapturedEvent.cpp
				client_MoveRightCapturedEvent.cpp
				client_MoveLeftCapturedEvent.cpp
				client_ConsoleDrawer.cpp
				client_DrawableFactory.cpp
				client_BeamDrawable.cpp
				client_ClosedConnectionDrawable.cpp
				client_DynamiteDrawable.cpp
				client_EndTurnDrawable.cpp
				client_RadiocontrolledDrawable.cpp
				client_StageDrawable.cpp
				client_StartTurnDrawable.cpp
				client_TurnTimeDrawable.cpp
				client_WormDrawable.cpp
				client_SdlWindow.cpp
				client_SdlException.cpp
				client_Area.cpp
				client_SdlTexture.cpp
				client_Main.cpp
				../common/common_SocketProtocol.cpp
				../common/common_Socket.cpp
				../common/common_Thread.cpp
				../common/common_Lock.cpp)

target_link_libraries(worms_client pthread SDL2 SDL2_image)