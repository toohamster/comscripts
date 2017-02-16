/**
 * jQuery fetch plugin v0.1
 * https://github.com/toohamster/jquery-fetch
 *
 * @author toohamster, 2016
 * @license MIT License <http://opensource.org/licenses/MIT>
 */
(function($) {
	'use strict';

	// 实现 异步 ajax队列,解决浏览器自身对http并发请求限制

	var Queue = function(){
		var items = [];

		this.add = function()
		{
			for (var i=0;i<arguments.length;i++)
			{
				if (arguments[i]) items.push(arguments[i]);
			}
		}
		this.size = function()
		{
			return items.length;
		}
		this.empty = function()
		{
			items = [];
		}
		this.next = function()
		{
			return items.shift();
		}
	};

	Queue._ooid = 1000;
	Queue.ooid = function(){return Queue._ooid++;}

	var Fetch = function(){
		this.queue = new Queue();
		this.uniqueIds = {};
		this.max = this.limit();
		this.alives = [];
	};

	Fetch.prototype.checking = function()
	{
		if ( this.alives.length >= this.max )
		{
			console.log("Has reached the upper limit: " + this.max);
			return false;
		}
		return this.execute();
	}

	Fetch.prototype.limit = function()
	{
		return 3;
	}

	Fetch.prototype.ajax = function(opts)
	{
		// uniqueId 用于替换功能
		var uniqueId = opts.uniqueId ? $.trim(uniqueId) : false;
		if ('' === uniqueId) uniqueId = false;

		var obj = {
			ooid: Queue.ooid(),
			uniqueId: uniqueId,
			ajax: opts
		};

		if ( uniqueId )
		{
			this.uniqueIds[ uniqueId ] = obj.ooid;
		}
		
		this.queue.add(obj);
	}
	
	Fetch.prototype.execute = function()
	{
		if ( this.queue.size() < 1 ) return false;

		var that = this;
		var task = this.queue.next();
		
		if (task)
		{
			if (task.uniqueId && (this.uniqueIds[ task.uniqueId ] !== task.ooid))
			{
				console.log("Item has be covered: " + task.uniqueId);
				return false;
			}

			that.alives.push(1);

			var ajax = $.extend({}, task.ajax);
			ajax.ooid = task.ooid;

			var fn = ajax.complete;
			ajax.complete = function(xhr, status)
			{
				if ( console.warn )
				{
					console.warn("ajax complete!!!: ", this.ooid);
				}
				
				that.alives.shift();
				
				if ( console.warn )
				{
					console.warn("alives: %d, queue size:%d!!!: ", that.alives.length, that.queue.size());
				}
				
				if (fn)
				{
					fn.call(this, xhr, status);
				}
				
			}
			$.ajax(ajax);
		}
	}

	$.fetch = new Fetch();

	// 加定时器
	window.setInterval("$.fetch.checking()",100);
	
}(jQuery));
