#include "Player.h"

void Player::ClientCommandsInit()
{

	cerSet.AddEventResponse(new Event(
		"patchver",
		EV_CONSOLE,
		NULL,
		NULL,
		"Print current patch version"
	),
		&Player::AdminLoginEvent);
}

void Player::PatchVersionEvent(Event * ev)
{
	gi.SendServerCommand(client->ps.clientNum, "print \"" PATCH_NAME " version " PATCH_VERSION " (" PATCH_STAGE ")\n\"" );
	gi.SendServerCommand(client->ps.clientNum, "print \"================\n\"" );
}