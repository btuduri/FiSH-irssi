#define MODULE_NAME "fish"

#include <irssi-config.h>

#include <common.h>
#include <core/servers.h>
#include <core/settings.h>
#include <core/levels.h>
#include <core/signals.h>
#include <core/commands.h>
#include <core/queries.h>
#include <core/channels.h>
#include <core/recode.h>
#include <core/servers.h>
#include <fe-common/core/printtext.h>
#include <fe-common/core/window-items.h>
#include <fe-common/core/keyboard.h>
#include <fe-common/irc/module-formats.h>
#include <irc/core/irc.h>

#ifdef ischannel
#undef ischannel
#endif

#include <irc/core/irc-commands.h>
#include <irc/core/irc-servers.h>

void irssi_redraw(void);

QUERY_REC *irc_query_create(const char *server_tag, const char *nick,
			    int automatic);
