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
  * [get(key: string): Buffer|undefined](#getkey-string-bufferundefined)
  * [exist(key: string): boolean](#existkey-string-boolean)
  * [touch(key: string, expiration: integer): this](#touchkey-string-expiration-integer-this)
  * [delete(key: string): this](#deletekey-string-this)
  * [increment(key: string, offset?: integer=1): integer](#incrementkey-string-offset-integer1-integer)
  * [decrement(key: string, offset?: integer=1): integer](#decrementkey-string-offset-integer1-integer)

## Requirements

* `memcached` >= 1.4.14
* `libmemcached` >= 1.0.18
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
const MemcachedClient = require('libmemcached')
~~~

## API

### constructor(config: string)

Initialize client.

`config` parameter is a [libMemcached configuration](http://docs.libmemcached.org/libmemcached_configuration.html) string.

~~~js
const mcc = new MemcachedClient('--SERVER=127.0.0.1')
~~~

### set(key: string, value: Buffer|string|number, expiration?:integer=0): this

Store item.

~~~js
mcc.set('key', 'val')
~~~

Function throws error when:

* key is not provided
* when value is not provided
* when value is boolean, null, undefined, function, object or array

~~~js
try {
  mcc.set('key', true)
}
catch(err) {
  console.error(err)
}
~~~

### add(key: string, value: Buffer|string|number, expiration?:integer=0): this

Add item. If key does exist - do nothing.

~~~js
mcc.add('key', 'val')
~~~

Function throws error when:

* key is not provided
* when value is not provided
* when value is boolean, null, undefined, function, object or array

~~~js
try {
  mcc.add('key', true)
}
catch(err) {
  console.error(err)
}
~~~

### replace(key: string, value: Buffer|string|number, expiration?:integer=0): this

Replace item. If key doesn't exist - do nothing.

~~~js
mcc.replace('key', 'val')
~~~

Function throws error when:

* key is not provided
* when value is not provided
* when value is boolean, null, undefined, function, object or array

~~~js
try {
  mcc.replace('key', true)
}
catch(err) {
  console.error(err)
}
~~~

### get(key: string): Buffer|undefined

Get item.

~~~js
let val = mcc.get('key')
~~~

Function throws error when:

* key is not provided

~~~js
try {
  let key
  let val = mcc.get(key)
}
catch(err) {
  console.error(err)
}
~~~

Function returns `undefined` when key doesn't exist.

### exist(key: string): boolean

Determine if a item exists.

~~~js
if (mcc.exist('key')) {
  console.log('key exist')
} else {
  console.log('key doesn\'t exist')
}
~~~

Function throws error when:

* key is not provided

~~~js
try {
  let key
  mcc.exist(key)
}
catch(err) {
  console.error(err)
}
~~~

### touch(key: string, expiration: integer): this

Update the expiration time of an existing item without fetching it.

~~~js
mcc.touch('key', 100)
~~~

Function throws error when:

* key is not provided
* expiration isn't integer

~~~js
try {
  mcc.touch('key', 1.23)
}
catch(err) {
  console.error(err)
}
~~~

### delete(key: string): this

Remove a item.

~~~js
mcc.delete('key')
~~~

Function throws error when:

* key is not provided
* key is not exist

~~~js
try {
  mcc.delete('not_existent_key')
}
catch(err) {
  console.error(err)
}
~~~

### increment(key: string, offset?: integer=1): integer

Incrementing item.

~~~js
let key = mcc.increment('key', 10)
~~~

Function throws error when:

* key is not provided
* key is not exist
* item is not integer
* offset is not integer

~~~js
try {
  let key = mcc.increment('key', 10.1)
}
catch(err) {
  console.error(err)
}
~~~

### decrement(key: string, offset?: integer=1): integer

Decrementing item.

~~~js
let key = mcc.decrement('key', 10)
~~~

Function throws error when:

* key is not provided
* key is not exist
* item is not integer
* offset is not integer

~~~js
try {
  let key = mcc.decrement('key', 10.1)
}
catch(err) {
  console.error(err)
}
~~~
