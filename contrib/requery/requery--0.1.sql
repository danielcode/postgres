/* contrib/test_parser/test_parser--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION requery" to load this file. \quit

CREATE FUNCTION requery(cstring)
RETURNS cstring
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

