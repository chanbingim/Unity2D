#if UNITY_EDITOR
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

        BuildReport report = BuildPipeline.BuildPlayer(GetScenePaths(), exePath,
            BuildTarget.StandaloneWindows64, BuildOptions.None);

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

        BuildReport report = BuildPipeline.BuildPlayer(GetScenePaths(), appPath,
            BuildTarget.StandaloneOSX, BuildOptions.None);

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

    static string[] GetScenePaths()
    {
        string[] scenes = new string[EditorBuildSettings.scenes.Length];
        for (int i = 0; i < scenes.Length; i++)
            scenes[i] = EditorBuildSettings.scenes[i].path;
        return scenes;
    }
}
#endif
