hook = {}
hook.hooks = {}

function hook.add(name, id, func)
    if not hooks.hooks[name] then
        hook.hooks[name] = {}
    end
    hook.hooks[name][id] = func
end

function hook.del(name, id)
    if hooks.hook[name] then
        hooks.hook[name][id] = nil
    end
end

function hook.Run(name, ...)
    if not hook.hooks[name] then return end
    for _, func in pairs(hook.hooks[name]) do
        func(...)
    end
end