PostgreSQL Wire Protocol Experiment
===================================

DRAFT
-----

Original PostgreSQL README file
-------------------------------
The original PostgreSQL README file is [here](postgres/blob/master/README).

Overview
--------
This is an experiment to see what happens if SQL isn't used as a wire protocol for relational database access.

The reasoning is as follows:
* Most sophisticated relational database libraries (including ORMs) store queries internally as expression trees.
* These expression trees are converted to SQL for transmission to a database.
* The database then parses the SQL into an expression tree.
* In theory, the expression tree can be passed directly from the client to the server, rather than going through
  the intermediate SQL conversion step.

Status
------
As at the date of writing (12/16/2012) this is a minimally viable proof of concept:
* It can execute simple SQL arithmetic expressions.  (E.g. "select 1 + 2;")
* It can select simple columns from tables (no namespacing, etc.)  (E.g. "select first_name from users;")
* It can name selected columns (E.g. "select 2 * 5 as result;")

Solution Components
-------------------
There are two repositories associated with this experiment:
* A modified version of PostgreSQL that can accept a serialized expression tree.
* A modified version of ruby-pg, the ruby client-side interface for PostgreSQL.
  This component links to customized PostgreSQL libraries that parse SQL to an expression tree, before passing
  that expression tree to the PostgreSQL server.

Building
--------

### Install Prefix
To be sure you don't break your existing Postgresql installation, we'll install somewhere else:

    export INSTALL_PREFIX="${HOME}/test-postgresql"
    export DB_PREFIX="${HOME}/testdb"
    export DB_NAME="testdb"

### Postgresql
1. Download, unpack and cd
2. Build and install

		export CFLAGS="-g -fPIC"
		autoconf
		./configure --prefix=${INSTALL_PREFIX} --enable-debug --with-libxml
		make && make install

### ruby-pg
1. Set path
   PATH="${INSTALL_PREFIX}/bin:$PATH"; export PATH
2. Download, unpack and cd
3. Build and install

		rake install_gem

Testing
--------
### Setup test database
1. Create database
		initdb -D ${DB_PREFIX}
2. Run postgresql server
		postgres -D ${DB_PREFIX}
3. Create test table

		psql ${DB_NAME}
		create table test (num integer, str varchar(50));
		insert into test values (14, 'Test');
		^D

### Run client
	irb
	require 'pg'
	conn = PG.connect( host: "localhost", dbname: ENV["DB_PREFIX"])
	x = conn.exec "select * from test;"
	x.first

Build Notes
-----------------
### Build Environment

My development system runs FreeBSD 9.0.  To build in this environment, you must upgrade GCC (I'm using 4.8).

