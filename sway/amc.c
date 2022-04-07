#include <stdio.h>
#include <wlr/util/amc.h>
#include "sway/tree/view.h"
#include "sway/output.h"

char *sway_surface_geo(char *prefix, struct wlr_surface *surface) {
	static char buf[8192];
	char *bp = buf;

	if (!surface) {
		bp += sprintf(bp, "AMC GEO no surface");
		return buf;
	}

	bp += sprintf(bp, wlr_surface_geo(prefix, surface));

	struct sway_view *view = view_from_wlr_surface(surface);

	struct sway_output *effective_output = NULL;
	if (view && view->container) {
		 effective_output = container_get_effective_output(view->container);
	}

	if (effective_output) {
		bp += sprintf(bp, "  %6s %5g", effective_output->wlr_output->name, effective_output->wlr_output->scale);
	} else {
		bp += sprintf(bp, "              ");
	}

	if (view) {
		bp += sprintf(bp, "   vg: %4d,%4d %4dx%4d",
				view->geometry.x, view->geometry.y,
				view->geometry.width, view->geometry.height
				);
	} else {
		bp += sprintf(bp, "   vg:                    ");
	}

	if (view && view->container) {
		bp += sprintf(bp, "   cc: %5g,%5g %5gx%5g %5g,%5g %5gx%5g",
				view->container->current.x, view->container->current.y,
				view->container->current.width, view->container->current.height,
				view->container->current.content_x, view->container->current.content_y,
				view->container->current.content_width, view->container->current.content_height
				);
	} else {
		bp += sprintf(bp, "   cc:                                                ");
	}

	return buf;
}

