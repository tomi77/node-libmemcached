# libmemcached

[![Build Status](https://travis-ci.org/tomi77/node-libmemcached.svg?branch=master)](https://travis-ci.org/tomi77/node-libmemcached)

Node.js bindings to the [libMemcached](http://libmemcached.org/) library.

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [API](#api)
  * [constructor(config: string)](#constructorconfig-string)
  * [set(key: string, value: Buffer|string|number, expiration?:integer=0): this](#setkey-string-value-bufferstringnumber-expirationinteger0-this)
  * [add(key: string, value: Buffer|string|number, expiration?:integer=0): this](#addkey-string-value-bufferstringnumber-expirationinteger0-this)
  * [replace(key: string, value: Buffer|string|number, expiration?:integer=0): this](#replacekey-string-value-bufferstringnumber-expirationinteger0-this)
  * [get(key: string): Buffer](#getkey-string-buffer)
  * [exist(key: string): boolean](#existkey-string-boolean)
  * [touch(key: string, expiration: integer): this](#touchkey-string-expiration-integer-this)
  * [delete(key: string): this](#deletekey-string-this)
  * [increment(key: string, offset?: integer=1): integer](#incrementkey-string-offset-integer1-integer)
  * [decrement(key: string, offset?: integer=1): integer](#decrementkey-string-offset-integer1-integer)

## Requirements

* `libmemcached`
* `libmemcached-dev`
* `gcc` with c++11

## Installation

~~~sh
npm install libmemcached --save
~~~

or

~~~sh
yarn add libmemcached
~~~

## Usage

~~~js
const MemcachedClient = require('libmemcached');

const mcc = new MemcachedClient('--SERVER=127.0.0.1');

console.log(mcc.get('test'));
~~~

## API

### constructor(config: string)

Initialize client.

`config` parameter is a [libMemcached configuration](http://docs.libmemcached.org/libmemcached_configuration.html) string.

### set(key: string, value: Buffer|string|number, expiration?:integer=0): this

Store item.

### add(key: string, value: Buffer|string|number, expiration?:integer=0): this

Add item.

### replace(key: string, value: Buffer|string|number, expiration?:integer=0): this

Replace item.

### get(key: string): Buffer

Get item.

### exist(key: string): boolean

Determine if a item exists.

### touch(key: string, expiration: integer): this

Update the expiration time of an existing item without fetching it.

### delete(key: string): this

Remove a item.

### increment(key: string, offset?: integer=1): integer

Incrementing item.

### decrement(key: string, offset?: integer=1): integer

Decrementing item.
