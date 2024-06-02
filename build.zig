const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) !void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target: std.Build.ResolvedTarget = b.standardTargetOptions(.{});
    // Standard optimization options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall. Here we do not
    // set a preferred release mode, allowing the user to decide how to optimize.
    const optimize: std.builtin.OptimizeMode = b.standardOptimizeOption(.{});
    const defaults: Options = Options{};
    const options: Options = Options{
        .shared = b.option(bool, "shared", "Compile as shared library") orelse defaults.shared,
        .module_array = b.option(bool, "module_array", "add the array module") orelse defaults.module_array,
        .module_data_structures = b.option(bool, "module_data_structures", "add the data_structures module") orelse defaults.module_data_structures,
        .module_endianess = b.option(bool, "module_endianess", "add the endianess module") orelse defaults.module_endianess,
        .module_error = b.option(bool, "module_error", "add the error module") orelse defaults.module_error,
        .module_file = b.option(bool, "module_file", "add the file module") orelse defaults.module_file,
        .module_io = b.option(bool, "module_io", "add the io module") orelse defaults.module_io,
        .module_math = b.option(bool, "module_math", "add the math module") orelse defaults.module_math,
        .module_memory = b.option(bool, "module_memory", "add the memory module") orelse defaults.module_memory,
        .module_sockets = b.option(bool, "module_sockets", "add the sockets module") orelse defaults.module_sockets,
        .module_string = b.option(bool, "module_string", "add the string module") orelse defaults.module_string,
        .module_vector = b.option(bool, "module_vector", "add the vector module") orelse defaults.module_vector,
    };

    const lib: *std.Build.Step.Compile = try compileClib(b, target, optimize, options);
    b.installArtifact(lib);
}

pub const Options = struct {
    shared: bool = false,
    module_array: bool = true,
    module_data_structures: bool = true,
    module_endianess: bool = true,
    module_error: bool = true,
    module_file: bool = true,
    module_io: bool = true,
    module_math: bool = true,
    module_memory: bool = true,
    module_sockets: bool = true,
    module_string: bool = true,
    module_vector: bool = true,
    clib_dependency_name: []const u8 = "clib",
};

pub fn addClib(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode, options: Options) !*std.Build.Step.Compile {
    const clib_dep: *std.Build.Dependency = b.dependency(options.clib_dependency_name, .{
        .target = target,
        .optimize = optimize,
        .shared = options.shared,
        .module_array = options.module_array,
        .module_data_structures = options.module_data_structures,
        .module_endianess = options.module_endianess,
        .module_error = options.module_error,
        .module_file = options.module_file,
        .module_io = options.module_io,
        .module_math = options.module_math,
        .module_memory = options.module_memory,
        .module_sockets = options.module_sockets,
        .module_string = options.module_string,
        .module_vector = options.module_vector,
    });
    const clib: *std.Build.Step.Compile = clib_dep.artifact("clib");
    return clib;
}

fn compileClib(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode, options: Options) !*std.Build.Step.Compile {
    var flags_arr: std.ArrayListUnmanaged([]const u8) = .{};
    defer flags_arr.deinit(b.allocator);
    try flags_arr.appendSlice(b.allocator, &[_][]const u8{ "-Wall", "-Wextra" });
    const clib: *std.Build.Step.Compile = if (options.shared)
        b.addSharedLibrary(.{
            .name = "clib",
            .target = target,
            .optimize = optimize,
        })
    else
        b.addStaticLibrary(.{
            .name = "clib",
            .target = target,
            .optimize = optimize,
        });
    clib.linkLibC();
    clib.addIncludePath(b.path("include"));
    clib.addIncludePath(b.path("src/data_structures"));
    var c_source_files = try std.ArrayList([]const u8).initCapacity(b.allocator, 1);
    defer c_source_files.deinit();
    if (options.module_array) {
        const path: []const u8 = b.path("src/array").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_ARRAY", "1");
    }
    if (options.module_data_structures) {
        const path: []const u8 = b.path("src/data_structures").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_DATA_STRUCTURES", "1");
    }
    if (options.module_endianess) {
        const path: []const u8 = b.path("src/endianess").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_ENDIANESS", "1");
    }
    if (options.module_error) {
        const path: []const u8 = b.path("src/error").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_ERROR", "1");
    }
    if (options.module_file) {
        const path: []const u8 = b.path("src/file").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_FILE", "1");
    }
    if (options.module_io) {
        const path: []const u8 = b.path("src/io").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_IO", "1");
    }
    if (options.module_math) {
        const path: []const u8 = b.path("src/math").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_MATH", "1");
    }
    if (options.module_memory) {
        const path: []const u8 = b.path("src/memory").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_MEMORY", "1");
    }
    if (options.module_sockets) {
        const path: []const u8 = b.path("src/sockets").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_SOCKETS", "1");
    }
    if (options.module_string) {
        const path: []const u8 = b.path("src/string").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_STRING", "1");
    }
    if (options.module_vector) {
        const path: []const u8 = b.path("src/vector").getPath(b);
        const files: []const []const u8 = try getAllFiles(b, path);
        try c_source_files.appendSlice(files);
        clib.root_module.addCMacro("CLIB_INCLUDE_VECTOR", "1");
    }

    var c_source_filesList = try std.ArrayList([]const u8).initCapacity(b.allocator, c_source_files.items.len);

    for (c_source_files.items) |path| {
        var out = try b.allocator.alloc(u8, path.len - b.path("").getPath(b).len + 1);
        _ = std.mem.replace(u8, path, b.path("src").getPath(b), ".", out);
        {
            const tmp = try b.allocator.alloc(u8, out.len);
            defer b.allocator.free(tmp);
            @memcpy(tmp, out);
            b.allocator.free(out);
            out = try b.allocator.alloc(u8, tmp.len - 4);
            _ = std.mem.copyForwards(u8, out, tmp[0 .. tmp.len - 4]);
        }
        try c_source_filesList.append(b.dupe(out));
        std.debug.print("file: {s}\n", .{out});
        b.allocator.free(out);
    }

    clib.root_module.addCSourceFiles(.{
        .root = b.path("src"),
        .files = c_source_filesList.items,
        .flags = flags_arr.items,
    });

    return clib;
}

fn getAllFiles(b: *std.Build, path: []const u8) ![]const []const u8 {
    var sources = std.ArrayList([]const u8).init(b.allocator);

    var dir: std.fs.Dir = try std.fs.openDirAbsolute(path, .{ .iterate = true });
    defer dir.close();

    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const extension: []const u8 = ".c";
    while (try walker.next()) |entry| {
        if (entry.kind == .directory) {
            try sources.appendSlice(try getAllFiles(b, entry.path));
        }
        if (std.mem.eql(u8, extension, std.fs.path.extension(entry.basename))) {
            const full_path = try std.fs.path.join(b.allocator, &[_][]const u8{ path, entry.path });

            try sources.append(b.dupe(full_path));
        }
    }
    return sources.items;
}
