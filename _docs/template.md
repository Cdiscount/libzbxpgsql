---
layout: page
title: Template
permalink: /template/
---

A comprehensive Zabbix template is included to demonstrate the use of the agent
keys made available in this module. It is not recommended to use this template
out-of-the-box in production without first configuring the check intervals,
configuration macros, discovery rule filters, etc. to suit your environment.

Import the `template_postgresql_server.xml` template into Zabbix to get
started.

Once applied to a host, the template will discover all available tablespaces,
databases and tables accessible to the configured user account and create items
and graphs for effective monitoring.

For a typical, PostgreSQL server hosting only Zabbix, this will create around
6000 item checks and 2500 graphs if no filtering is applied.

Please note that the template uses [Active checks](https://www.zabbix.com/documentation/2.4/manual/appendix/items/activepassive)
and so a restart of the agent may be required for the new template items to be
made known to the agent.

## Usage

* Import [template_postgresql_server.xml](https://raw.githubusercontent.com/cavaliercoder/libzbxpgsql/master/template_postgresql_server.xml)
  from the source repository. For information on importing Templates, see the [Zabbix manual](https://www.zabbix.com/documentation/2.4/manual/xml_export_import).

* Configure your PostgreSQL connection details on the desired host using the
  provided [macros](#macros).

* Apply the newly imported `Template PostgreSQL Server` template to your
  selected host.

* Add [Discovery Filters](https://www.zabbix.com/documentation/2.4/manual/discovery/low_level_discovery?s[]=filters)
  to the Discovery Rules on the __Host__ so that only the desired databases,
  tables, etc. are created during discovery.

  For example, to monitor only the `zabbix` database, add a Filter to the
  `Discover PostgreSQL Databases` discovery rule with:

  `{#DATABASE}` matches `^zabbix$`

  To monitor only the History and Trends tables for Zabbix, add a Filter to the
  `Discover PostgreSQL Tables` discovery rule with:

  `{#DATABASE}` *matches* `^zabbix$` *and* `{#TABLE}` *matches* `^history.*|^trend.*`

  ![Discovery rule filter screenshot]({{ site.baseurl }}/assets/filters.png)

* Restart the Zabbix Agent (or wait for [RefreshActiveChecks](https://www.zabbix.com/documentation/2.4/manual/appendix/config/zabbix_agentd?s[]=RefreshActiveChecks)
  to expire) so the agent becomes aware of the new configuration.

* Explore *Latest Data* and *Graphs* to make use of the captured data.
  
  ![Latest data screenshot]({{ site.baseurl }}/assets/latestdata.png)


### Macros

The template includes configurable macros which should be configured on all
hosts to which the template is applied. These macros are substituted into the
connection parameters for all PostgreSQL item keys in the template.

* `{$PG_HOST}`      - PostgreSQL server (Default: `localhost`)
* `{$PG_PORT}`      - TCP Port for connection (Default: module default)
* `{$PG_USER}`      - User account for authentication (Default: `postgres`)
* `{$PG_PASSWD}`    - User password for authentication (Default: module default)
* `{$PG_DB}`        - Database to connect to (Default: module default)
