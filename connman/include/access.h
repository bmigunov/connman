/*
 *  Connection Manager
 *
 *  Copyright (C) 2017 Jolla Ltd. All rights reserved.
 *  Contact: Slava Monich <slava.monich@jolla.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#ifndef __CONNMAN_ACCESS_H
#define __CONNMAN_ACCESS_H

#include <glib.h>

G_BEGIN_DECLS

enum connman_access {
	CONNMAN_ACCESS_DENY,
	CONNMAN_ACCESS_ALLOW
};

struct connman_access_service_policy;
struct connman_access_service_policy_impl;

struct connman_access_driver {
	const char *name;
	const char *default_service_policy;
	struct connman_access_service_policy_impl *(*service_policy_create)
		(const char *spec);
	void (*service_policy_free)
		(struct connman_access_service_policy_impl *policy);
	enum connman_access (*service_get_property)
		(struct connman_access_service_policy_impl *policy,
			const char *sender, const char *name,
			enum connman_access default_access);
	enum connman_access (*service_set_property)
		(struct connman_access_service_policy_impl *policy,
			const char *sender, const char *name,
			enum connman_access default_access);
};

int connman_access_driver_register(const struct connman_access_driver *d);
void connman_access_driver_unregister(const struct connman_access_driver *d);
const char *connman_access_default_service_policy(void);

struct connman_access_service_policy *connman_access_service_policy_create(
							const char *spec);
void connman_access_service_policy_free(
				struct connman_access_service_policy *policy);
enum connman_access connman_access_service_get_property(
	struct connman_access_service_policy *policy, const char *sender,
	const char *name, enum connman_access default_access);
enum connman_access connman_access_service_set_property(
	struct connman_access_service_policy *policy, const char *sender,
	const char *name, enum connman_access default_access);

G_END_DECLS

#endif /* __CONNMAN_ACCESS_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 8
 * indent-tabs-mode: t
 * End:
 */
