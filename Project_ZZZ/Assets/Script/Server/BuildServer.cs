#if UNITY_EDITOR
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using UnityEditor;
using UnityEditor.Build.Reporting;
using UnityEngine;

public class MultiplayerBuildAndRun
{
    [MenuItem("Tools/Run Multiplayer/Win64/1 Players")]
    static void PerformWin64Build1() => PerformWin64Build(1);

    #region Window
    [MenuItem("Tools/Run Multiplayer/Win64/2 Players")]
    static void PerformWin64Build2() => PerformWin64Build(2);

    [MenuItem("Tools/Run Multiplayer/Win64/3 Players")]
    static void PerformWin64Build3() => PerformWin64Build(3);

    [MenuItem("Tools/Run Multiplayer/Win64/4 Players")]
    static void PerformWin64Build4() => PerformWin64Build(4);

    static void PerformWin64Build(int playerCount)
    {
        EditorUserBuildSettings.SwitchActiveBuildTarget(
            BuildTargetGroup.Standalone, BuildTarget.StandaloneWindows64);

        string projectName = GetProjectName();
        string buildFolder = Path.Combine("Builds", "Win64", projectName);
        string exePath = Path.Combine(buildFolder, projectName + ".exe");
        Directory.CreateDirectory(buildFolder);

        BuildReport report = BuildPipeline.BuildPlayer(
            GetEnabledScenePaths(), exePath,
            BuildTarget.StandaloneWindows64, BuildPlayerOptions());

        if (report.summary.result != BuildResult.Succeeded)
        {
            return;
        }

        string fullExe = Path.GetFullPath(exePath);
        string workDir = Path.GetFullPath(buildFolder);

        for (int i = 0; i < playerCount; i++)
        {
            Process.Start(new ProcessStartInfo
            {
                FileName = fullExe,
                WorkingDirectory = workDir,
                UseShellExecute = true
            });
        }
    }

    #endregion

    #region Mac

    [MenuItem("Tools/Run Multiplayer/Mac/1 Players")]
    static void PerformMacBuild1() => PerformMacBuild(1);

    [MenuItem("Tools/Run Multiplayer/Mac/2 Players")]
    static void PerformMacBuild2() => PerformMacBuild(2);

    [MenuItem("Tools/Run Multiplayer/Mac/3 Players")]
    static void PerformMacBuild3() => PerformMacBuild(3);

    [MenuItem("Tools/Run Multiplayer/Mac/4 Players")]
    static void PerformMacBuild4() => PerformMacBuild(4);

    static void PerformMacBuild(int playerCount)
    {
        EditorUserBuildSettings.SwitchActiveBuildTarget(
            BuildTargetGroup.Standalone, BuildTarget.StandaloneOSX);

        string projectName = GetProjectName();
        string buildFolder = Path.Combine("Builds", "Mac", projectName);
        string appPath = Path.Combine(buildFolder, projectName + ".app");
        Directory.CreateDirectory(buildFolder);

        BuildReport report = BuildPipeline.BuildPlayer(
            GetEnabledScenePaths(), appPath,
            BuildTarget.StandaloneOSX, BuildPlayerOptions());

        if (report.summary.result != BuildResult.Succeeded)
        {
            return;
        }

        string fullApp = Path.GetFullPath(appPath);
        for (int i = 0; i < playerCount; i++)
        {
            Process.Start(new ProcessStartInfo
            {
                FileName = "/usr/bin/open",
                Arguments = "-n \"" + fullApp + "\"",
                UseShellExecute = false
            });
        }
    }

    #endregion

    static string GetProjectName()
    {
        return Path.GetFileName(Path.GetDirectoryName(Application.dataPath));
    }

    /// <summary>
    /// Matches File → Build Settings: only scenes with the checkbox enabled are built.
    /// Including disabled scenes changes build order and the startup scene, which can
    /// break rendering (e.g. pink materials if the first scene is not the real game scene).
    /// </summary>
    static string[] GetEnabledScenePaths()
    {
        var scenes = new List<string>();
        foreach (EditorBuildSettingsScene s in EditorBuildSettings.scenes)
        {
            if (s.enabled && !string.IsNullOrEmpty(s.path))
                scenes.Add(s.path);
        }

        if (scenes.Count == 0)
            UnityEngine.Debug.LogError("Multiplayer build: no scenes enabled in File → Build Settings.");

        return scenes.ToArray();
    }

    static BuildOptions BuildPlayerOptions()
    {
        BuildOptions o = BuildOptions.None;
        if (EditorUserBuildSettings.development)
            o |= BuildOptions.Development;
        if (EditorUserBuildSettings.allowDebugging)
            o |= BuildOptions.AllowDebugging;
        if (EditorUserBuildSettings.connectProfiler)
            o |= BuildOptions.ConnectWithProfiler;
        if (EditorUserBuildSettings.buildWithDeepProfilingSupport)
            o |= BuildOptions.EnableDeepProfilingSupport;
        return o;
    }
}
#endif
