local repo = "https://raw.githubusercontent.com/cloudsense-pub/UELinoriaLib/main/"
local Library = loadstring(game:HttpGet(repo .. "Library.lua"))()
local ThemeManager = loadstring(game:HttpGet(repo .. "addons/ThemeManager.lua"))()
local SaveManager = loadstring(game:HttpGet(repo .. "addons/SaveManager.lua"))()

Library.ShowToggleFrameInKeybinds = true
Library.ShowCustomCursor = true
Library.NotifySide = "Right"

local Window = Library:CreateWindow({
    Title = "hooksenseㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤ",
    Center = true,
    AutoShow = true,
    Resizable = true,
    ShowCustomCursor = true,
    UnlockMouseWhileOpen = true,
    NotifySide = "Left",
    TabPadding = 8,
    MenuFadeTime = 0.2
})

task.spawn(function()
    local MainFrame = Library.Main
    if MainFrame then
        local TabContainer = MainFrame:FindFirstChild("TabContainer") or MainFrame:FindFirstChildOfClass("Frame")
        if TabContainer then
            local ScrollFrame = Instance.new("ScrollingFrame")
            ScrollFrame.Name = "ScrollingTabContainer"
            ScrollFrame.Size = UDim2.new(1, -20, 0, 32)
            ScrollFrame.Position = UDim2.new(0, 10, 0, 38)
            ScrollFrame.BackgroundTransparency = 1
            ScrollFrame.BorderSizePixel = 0
            ScrollFrame.ScrollBarThickness = 2
            ScrollFrame.ScrollingDirection = Enum.ScrollingDirection.X
            ScrollFrame.CanvasSize = UDim2.new(0, 0, 0, 0)
            ScrollFrame.ClipsDescendants = true
            ScrollFrame.Parent = MainFrame

            local Layout = Instance.new("UIListLayout")
            Layout.FillDirection = Enum.FillDirection.Horizontal
            Layout.SortOrder = Enum.SortOrder.LayoutOrder
            Layout.Padding = UDim.new(0, 6)
            Layout.Parent = ScrollFrame

            for _, child in ipairs(TabContainer:GetChildren()) do
                if child:IsA("TextButton") or child:IsA("GuiButton") then
                    child.Parent = ScrollFrame
                end
            end
            TabContainer:Destroy()

            Layout:GetPropertyChangedSignal("AbsoluteContentSize"):Connect(function()
                ScrollFrame.CanvasSize = UDim2.new(0, Layout.AbsoluteContentSize.X + 15, 0, 0)
            end)
        end
    end
end)

_G.SilentAimEnabled = false
_G.BulletTPEnabled = false
_G.WallCheckEnabled = false
_G.TeamCheckEnabled = false
_G.DieCheckEnabled = true
_G.LookAtEnabled = false
_G.FOVSize = 100
_G.FOVVisible = true
_G.TracerEnabled = true

_G.MobileAimbotEnabled = false
_G.AimbotSmoothness = 0.1
_G.AutoPredictionEnabled = false
_G.PredictionValue = 0.1
_G.AimbotTargetPart = "Head"

_G.JumpSmooth = 1
_G.SmoothX = 1
_G.SmoothZ = 1
_G.PermLockEnabled = false
_G.PermTargetList = {}
_G.GlobalFontSetting = Enum.Font.Cartoon

local RobloxFontsList = {}
for _, font in ipairs(Enum.Font:GetEnumItems()) do
    table.insert(RobloxFontsList, font.Name)
end
table.sort(RobloxFontsList)

_G.HitSoundMode = "None"
_G.HitSoundVolume = 2
local SoundIDs = {
    ["None"] = "None",
    ["Spark"] = "rbxassetid://110241936966089",
    ["Neverlose"] = "rbxassetid://18391691942",
    ["Rust"] = "rbxassetid://138750331387064",
    ["Fatality"] = "rbxassetid://111508823459652",
    ["Fatality 2"] = "rbxassetid://17802817724",
    ["Minecraft xp"] = "rbxassetid://17148249625",
    ["Minecraft"] = "rbxassetid://135478009117226",
    ["Skeet"] = "rbxassetid://80461265049096"
}

_G.HitNotifyEnabled = false
_G.HitNotifyStyle = "Center"
_G.HitNotifyAnimType = "Smooth"
_G.HitNotifyTransparency = 0.0
_G.HitNotifyPosX = 50
_G.HitNotifyPosY = 80
_G.HitNotifyDuration = 2.5
_G.HitNotifyColor = Color3.fromRGB(0, 255, 255)
local ActiveNotifications = {}

-- Hit Overlay Variables
_G.HitOverlayEnabled = false
_G.HitOverlayColor = Color3.fromRGB(255, 0, 0)

_G.SkyboxEnabled = false
_G.SelectedSkybox = "Minecraft"
local SkyboxIDs = {
    ["Minecraft"] = "rbxassetid://83591302868034",
    ["Minecraft 2"] = "rbxassetid://117301665698887",
    ["Skyblox 1"] = "rbxassetid://4951222008",
    ["Skyblox 2"] = "rbxassetid://4604073339",
    ["Skyblox 3"] = "rbxassetid://8464073887",
    ["Skyblox 4"] = "rbxassetid://90988519"
}

_G.FOVCircleColor = Color3.fromRGB(255, 255, 255)
_G.FOVCircleOutlineColor = Color3.fromRGB(0, 0, 0)
_G.TracerLineColor = Color3.fromRGB(255, 0, 0)
_G.TracerLineOutlineColor = Color3.fromRGB(0, 0, 0)
_G.TracerThickness = 1.0
_G.TracerOutlineThickness = 3.0

_G.FOVFillEnabled = false
_G.FOVFillTransparency = 0.2
_G.FOVFillColor1 = Color3.fromRGB(255, 0, 0)
_G.FOVFillColor2 = Color3.fromRGB(0, 255, 0)
_G.FOVFillColor3 = Color3.fromRGB(0, 0, 255)
_G.FOVFillRotateEnabled = false
_G.FOVFillRotateSpeed = 1
local currentRotationAngle = 0

_G.TargetPartMode = "Head"
_G.TransitionSpeed = 5
_G.MaxTargetDistance = 10000

_G.ESPEnabled = false
_G.ESPName = false
_G.ESPHighlights = false
_G.ESPHealth = false
_G.ColorBox = Color3.fromRGB(0, 255, 255)
_G.ColorName = Color3.fromRGB(255, 255, 255)

_G.AntiAimEnabled = false
_G.AntiAimMode = "Spin"
_G.AntiAimSpeed = 15
_G.JitterMode = "Multi"
_G.ThirdPersonEnabled = false
_G.ThirdPersonDistance = 12
_G.BhopEnabled = false
_G.BhopSpeedMultiplier = 1.5

local Camera = workspace.CurrentCamera
local Players = game.Players
local LocalPlayer = Players.LocalPlayer
local CoreGui = game:GetService("CoreGui")
local UserInputService = game:GetService("UserInputService")
local SoundService = game:GetService("SoundService")
local Lighting = game:GetService("Lighting")
local TweenService = game:GetService("TweenService")
local CurrentWeatherEffect = nil
local DisplayNameLabel, UsernameLabel, UserIdLabel, AvatarImage
local ESP_Storage = {}

local TargetGuiParent = LocalPlayer:WaitForChild("PlayerGui", 5) or (CoreGui:FindFirstChild("RobloxGui") or CoreGui)

local HitNotifyGui = Instance.new("ScreenGui")
HitNotifyGui.Name = "hooksense_HitNotifyGui"
HitNotifyGui.ResetOnSpawn = false
HitNotifyGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
HitNotifyGui.Parent = TargetGuiParent

local HitOverlayGui = Instance.new("ScreenGui")
HitOverlayGui.Name = "hooksense_HitOverlayGui"
HitOverlayGui.ResetOnSpawn = false
HitOverlayGui.IgnoreGuiInset = true
HitOverlayGui.DisplayOrder = 99999
HitOverlayGui.Parent = TargetGuiParent

local OverlayFrame = Instance.new("Frame")
OverlayFrame.Name = "HitOverlay"
OverlayFrame.Size = UDim2.new(1, 0, 1, 0)
OverlayFrame.BorderSizePixel = 0
OverlayFrame.BackgroundColor3 = _G.HitOverlayColor
OverlayFrame.BackgroundTransparency = 1
OverlayFrame.ZIndex = 99999
OverlayFrame.Parent = HitOverlayGui

local function TriggerHitOverlay()
    if not _G.HitOverlayEnabled then return end
    OverlayFrame.BackgroundColor3 = _G.HitOverlayColor
    
    local fadeIn = TweenService:Create(OverlayFrame, TweenInfo.new(0.05, Enum.EasingStyle.Quad, Enum.EasingDirection.Out), {BackgroundTransparency = 0.5})
    local fadeOut = TweenService:Create(OverlayFrame, TweenInfo.new(0.3, Enum.EasingStyle.Quad, Enum.EasingDirection.In), {BackgroundTransparency = 1})
    
    fadeIn:Play()
    fadeIn.Completed:Connect(function()
        task.wait(0.01)
        fadeOut:Play()
    end)
end

local function UpdateNotificationPositions()
    local spacing = 35
    for index, frame in ipairs(ActiveNotifications) do
        local rawX = _G.HitNotifyPosX / 100
        local rawY = _G.HitNotifyPosY / 100
        local offsetUp = (index - 1) * spacing
        local tweenInfo = TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out)
        local targetPosition
        if _G.HitNotifyStyle == "Left" then
            targetPosition = UDim2.new(rawX, 15, rawY, -offsetUp)
        elseif _G.HitNotifyStyle == "Center" then
            targetPosition = UDim2.new(rawX, 0, rawY, -offsetUp)
        else
            targetPosition = UDim2.new(rawX, -15, rawY, -offsetUp)
        end
        TweenService:Create(frame, tweenInfo, {Position = targetPosition}):Play()
    end
end

local function ShowCustomHitNotification(targetName, partName, damage)
    if not _G.HitNotifyEnabled then return end
    local NotifyFrame = Instance.new("Frame")
    NotifyFrame.Size = UDim2.new(0, 240, 0, 30)
    if _G.HitNotifyStyle == "Left" then
        NotifyFrame.AnchorPoint = Vector2.new(0, 1)
    elseif _G.HitNotifyStyle == "Center" then
        NotifyFrame.AnchorPoint = Vector2.new(0.5, 0.5)
    else
        NotifyFrame.AnchorPoint = Vector2.new(1, 1)
    end
    local rawX = _G.HitNotifyPosX / 100
    local rawY = _G.HitNotifyPosY / 100
    local finalPosition = UDim2.new(rawX, (_G.HitNotifyStyle == "Left" and 15 or (_G.HitNotifyStyle == "Right" and -15 or 0)), rawY, 0)
    NotifyFrame.BackgroundColor3 = Color3.fromRGB(15, 15, 20)
    NotifyFrame.BorderSizePixel = 0
    NotifyFrame.ZIndex = 10
    NotifyFrame.Parent = HitNotifyGui

    local Corner = Instance.new("UICorner")
    Corner.CornerRadius = UDim.new(0, 5)
    Corner.Parent = NotifyFrame

    local Stroke = Instance.new("UIStroke")
    Stroke.Color = _G.HitNotifyColor
    Stroke.Thickness = 1.2
    Stroke.Parent = NotifyFrame

    local CheckmarkIcon = Instance.new("TextLabel")
    CheckmarkIcon.Name = "CheckmarkIcon"
    CheckmarkIcon.Size = UDim2.new(0, 20, 1, 0)
    CheckmarkIcon.Position = UDim2.new(0, 6, 0, 0)
    CheckmarkIcon.Font = Enum.Font.GothamBold
    CheckmarkIcon.TextSize = 12
    CheckmarkIcon.Text = "✓"
    CheckmarkIcon.TextColor3 = _G.HitNotifyColor
    CheckmarkIcon.BackgroundTransparency = 1
    CheckmarkIcon.TextXAlignment = Enum.TextXAlignment.Center
    CheckmarkIcon.Parent = NotifyFrame

    local TextLabel = Instance.new("TextLabel")
    TextLabel.Name = "NotifyTextLabel"
    TextLabel.Size = UDim2.new(1, -34, 1, 0)
    TextLabel.Position = UDim2.new(0, 28, 0, 0)
    TextLabel.Font = _G.GlobalFontSetting
    TextLabel.TextSize = 11
    TextLabel.TextWrapped = true
    TextLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
    TextLabel.BackgroundTransparency = 1
    TextLabel.TextXAlignment = Enum.TextXAlignment.Left
    TextLabel.Text = string.format("Hit %s in the %s for %s dmg", targetName, partName, tostring(damage))
    TextLabel.Parent = NotifyFrame

    if _G.HitNotifyAnimType == "Tween Inside" then
        local UIScale = Instance.new("UIScale")
        UIScale.Scale = 0.4
        UIScale.Parent = NotifyFrame
        NotifyFrame.Position = finalPosition
        NotifyFrame.BackgroundTransparency = _G.HitNotifyTransparency
        Stroke.Transparency = _G.HitNotifyTransparency
        TextLabel.TextTransparency = _G.HitNotifyTransparency
        CheckmarkIcon.TextTransparency = _G.HitNotifyTransparency
        TweenService:Create(UIScale, TweenInfo.new(0.2, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {Scale = 1}):Play()
    else
        NotifyFrame.Position = finalPosition + UDim2.new(0, 0, 0, 20)
        NotifyFrame.BackgroundTransparency = 1
        Stroke.Transparency = 1
        TextLabel.TextTransparency = 1
        CheckmarkIcon.TextTransparency = 1
        TweenService:Create(NotifyFrame, TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out), {Position = finalPosition, BackgroundTransparency = _G.HitNotifyTransparency}):Play()
        TweenService:Create(Stroke, TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out), {Transparency = _G.HitNotifyTransparency}):Play()
        TweenService:Create(TextLabel, TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out), {TextTransparency = _G.HitNotifyTransparency}):Play()
        TweenService:Create(CheckmarkIcon, TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.Out), {TextTransparency = _G.HitNotifyTransparency}):Play()
    end

    table.insert(ActiveNotifications, 1, NotifyFrame)
    UpdateNotificationPositions()

    task.delay(_G.HitNotifyDuration, function()
        local tweenInfo = TweenInfo.new(0.3, Enum.EasingStyle.Linear)
        local tween = TweenService:Create(NotifyFrame, tweenInfo, {BackgroundTransparency = 1})
        local tweenText = TweenService:Create(TextLabel, tweenInfo, {TextTransparency = 1})
        local tweenIcon = TweenService:Create(CheckmarkIcon, tweenInfo, {TextTransparency = 1})
        local tweenStroke = TweenService:Create(Stroke, tweenInfo, {Transparency = 1})
        if _G.HitNotifyAnimType == "Tween Inside" and NotifyFrame:FindFirstChildOfClass("UIScale") then
            TweenService:Create(NotifyFrame:FindFirstChildOfClass("UIScale"), TweenInfo.new(0.2, Enum.EasingStyle.Quart, Enum.EasingDirection.In), {Scale = 0.75}):Play()
        end
        tween:Play()
        tweenText:Play()
        tweenIcon:Play()
        tweenStroke:Play()
        tween.Completed:Connect(function()
            for i, frame in ipairs(ActiveNotifications) do
                if frame == NotifyFrame then
                    table.remove(ActiveNotifications, i)
                    break
                end
            end
            NotifyFrame:Destroy()
            UpdateNotificationPositions()
        end)
    end)
end

local function PlayHitSound()
    if _G.HitSoundMode == "None" or not SoundIDs[_G.HitSoundMode] then return end
    local Sound = Instance.new("Sound")
    Sound.SoundId = SoundIDs[_G.HitSoundMode]
    Sound.Volume = _G.HitSoundVolume
    Sound.PlayOnRemove = true
    Sound.Parent = SoundService
    Sound:Destroy()
end

local function UpdateSkybox()
    for _, obj in ipairs(Lighting:GetChildren()) do
        if obj:IsA("Sky") and (obj.Name == "hooksenseSky" or obj.Name == "Sky") then
            obj:Destroy()
        end
    end
    if _G.SkyboxEnabled and SkyboxIDs[_G.SelectedSkybox] then
        local assetId = SkyboxIDs[_G.SelectedSkybox]
        local success, result = pcall(function() return game:GetObjects(assetId)[1] end)
        if success and result and result:IsA("Sky") then
            local NewSky = result:Clone()
            NewSky.Name = "hooksenseSky"
            NewSky.Parent = Lighting
        else
            local NewSky = Instance.new("Sky")
            NewSky.Name = "hooksenseSky"
            NewSky.SkyboxBk = assetId
            NewSky.SkyboxDn = assetId
            NewSky.SkyboxFt = assetId
            NewSky.SkyboxLf = assetId
            NewSky.SkyboxRt = assetId
            NewSky.SkyboxUp = assetId
            NewSky.Parent = Lighting
        end
    end
end

-- =============================================================================
-- [UPGRADED ULTRA CYBERPUNK TARGET HUD SYSTEM - GREEN & BLACK THEME]
-- =============================================================================
local TargetGui = Instance.new("ScreenGui")
TargetGui.Name = "hooksenseTargetHudGui"
TargetGui.ResetOnSpawn = false
TargetGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
TargetGui.Parent = TargetGuiParent

local MainCanvas = Instance.new("CanvasGroup")
MainCanvas.Name = "MainTargetHUD"
MainCanvas.Size = UDim2.new(0, 280, 0, 90)
MainCanvas.AnchorPoint = Vector2.new(1, 0)
MainCanvas.Position = UDim2.new(1, -20, 0, 60)
MainCanvas.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
MainCanvas.BackgroundTransparency = 0.15 
MainCanvas.BorderSizePixel = 0
MainCanvas.GroupTransparency = 1 
MainCanvas.Visible = false
MainCanvas.Parent = TargetGui

local Corner = Instance.new("UICorner")
Corner.CornerRadius = UDim.new(0, 10)
Corner.Parent = MainCanvas

local Stroke = Instance.new("UIStroke")
Stroke.Color = Color3.fromRGB(255, 255, 255)
Stroke.Thickness = 1.8
Stroke.ApplyStrokeMode = Enum.ApplyStrokeMode.Border
Stroke.Parent = MainCanvas

local BorderGradient = Instance.new("UIGradient")
BorderGradient.Color = ColorSequence.new({
    ColorSequenceKeypoint.new(0, Color3.fromRGB(0, 255, 100)),
    ColorSequenceKeypoint.new(0.5, Color3.fromRGB(0, 150, 0)),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(0, 255, 100))
})
BorderGradient.Rotation = 45
BorderGradient.Parent = Stroke

local dragging = false
local dragInput
local dragStart
local startPos

local function update(input)
    local delta = input.Position - dragStart
    TweenService:Create(MainCanvas, TweenInfo.new(0.08, Enum.EasingStyle.OutQuad), {
        Position = UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X, startPos.Y.Scale, startPos.Y.Offset + delta.Y)
    }):Play()
end

MainCanvas.InputBegan:Connect(function(input)
    if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then
        dragging = true
        dragStart = input.Position
        startPos = MainCanvas.Position
        
        local connection
        connection = input.Changed:Connect(function()
            if input.UserInputState == Enum.UserInputState.End then
                dragging = false
                if connection then connection:Disconnect() end
            end
        end)
    end
end)

MainCanvas.InputChanged:Connect(function(input)
    if input.UserInputType == Enum.UserInputType.MouseMovement or input.UserInputType == Enum.UserInputType.Touch then
        dragInput = input
    end
end)

UserInputService.InputChanged:Connect(function(input)
    if dragging and (input == dragInput or input.UserInputType == Enum.UserInputType.Touch) then
        update(input)
    end
end)

local AvatarFrame = Instance.new("Frame")
AvatarFrame.Size = UDim2.new(0, 56, 0, 56)
AvatarFrame.Position = UDim2.new(0, 14, 0, 14)
AvatarFrame.BackgroundColor3 = Color3.fromRGB(15, 15, 22)
AvatarFrame.BorderSizePixel = 0
AvatarFrame.Parent = MainCanvas

local AvatarCorner = Instance.new("UICorner")
AvatarCorner.CornerRadius = UDim.new(1, 0) 
AvatarCorner.Parent = AvatarFrame

local AvatarStroke = Instance.new("UIStroke")
AvatarStroke.Color = Color3.fromRGB(0, 0, 0)
AvatarStroke.Thickness = 1.5
AvatarStroke.Parent = AvatarFrame

AvatarImage = Instance.new("ImageLabel")
AvatarImage.Size = UDim2.new(1, -4, 1, -4)
AvatarImage.Position = UDim2.new(0, 2, 0, 2)
AvatarImage.BackgroundTransparency = 1
AvatarImage.Parent = AvatarFrame

local ImgCorner = Instance.new("UICorner")
ImgCorner.CornerRadius = UDim.new(1, 0)
ImgCorner.Parent = AvatarImage

local InfoFrame = Instance.new("Frame")
InfoFrame.Size = UDim2.new(1, -95, 1, -40)
InfoFrame.Position = UDim2.new(0, 84, 0, 12)
InfoFrame.BackgroundTransparency = 1
InfoFrame.Parent = MainCanvas

DisplayNameLabel = Instance.new("TextLabel")
DisplayNameLabel.Size = UDim2.new(1, 0, 0, 18)
DisplayNameLabel.Font = _G.GlobalFontSetting
DisplayNameLabel.TextSize = 14
DisplayNameLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
DisplayNameLabel.TextXAlignment = Enum.TextXAlignment.Left
DisplayNameLabel.Text = "No Target"
DisplayNameLabel.BackgroundTransparency = 1
DisplayNameLabel.Parent = InfoFrame

UsernameLabel = Instance.new("TextLabel")
UsernameLabel.Size = UDim2.new(1, 0, 0, 14)
UsernameLabel.Position = UDim2.new(0, 0, 0, 18)
UsernameLabel.Font = _G.GlobalFontSetting
UsernameLabel.TextSize = 11
UsernameLabel.TextColor3 = Color3.fromRGB(140, 140, 155)
UsernameLabel.TextXAlignment = Enum.TextXAlignment.Left
UsernameLabel.Text = "@none"
UsernameLabel.BackgroundTransparency = 1
UsernameLabel.Parent = InfoFrame

UserIdLabel = Instance.new("TextLabel")
UserIdLabel.Size = UDim2.new(1, 0, 0, 12)
UserIdLabel.Position = UDim2.new(0, 0, 0, 32)
UserIdLabel.Font = _G.GlobalFontSetting
UserIdLabel.TextSize = 10
UserIdLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
UserIdLabel.TextXAlignment = Enum.TextXAlignment.Left
UserIdLabel.Text = "USER ID: --"
UserIdLabel.BackgroundTransparency = 1
UserIdLabel.Parent = InfoFrame

local HealthBackground = Instance.new("Frame")
HealthBackground.Size = UDim2.new(1, -28, 0, 5)
HealthBackground.Position = UDim2.new(0, 14, 1, -16)
HealthBackground.BackgroundColor3 = Color3.fromRGB(20, 25, 20)
HealthBackground.BorderSizePixel = 0
HealthBackground.Parent = MainCanvas

local HealthBarCorner = Instance.new("UICorner")
HealthBarCorner.CornerRadius = UDim.new(0, 4)
HealthBarCorner.Parent = HealthBackground

local HealthBar = Instance.new("Frame")
HealthBar.Size = UDim2.new(1, 0, 1, 0)
HealthBar.BackgroundColor3 = Color3.fromRGB(0, 255, 100)
HealthBar.BorderSizePixel = 0
HealthBar.Parent = HealthBackground

local MainBarCorner = Instance.new("UICorner")
MainBarCorner.CornerRadius = UDim.new(0, 4)
MainBarCorner.Parent = HealthBar

local isHudVisible = false
local function ToggleHUD(state)
    if state then
        if not isHudVisible then
            isHudVisible = true
            MainCanvas.Visible = true
            TweenService:Create(MainCanvas, TweenInfo.new(0.2, Enum.EasingStyle.Cubic, Enum.EasingDirection.Out), {GroupTransparency = 0}):Play()
        end
    else
        if isHudVisible then
            isHudVisible = false
            local fadeOut = TweenService:Create(MainCanvas, TweenInfo.new(0.2, Enum.EasingStyle.Cubic, Enum.EasingDirection.In), {GroupTransparency = 1})
            fadeOut:Play()
            fadeOut.Completed:Connect(function()
                if not isHudVisible then MainCanvas.Visible = false end
            end)
        end
    end
end
-- =============================================================================

local EspGui = Instance.new("ScreenGui")
EspGui.Name = "hooksenseModernEspGui"
EspGui.ResetOnSpawn = false
EspGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
EspGui.Parent = TargetGuiParent

local DeltaGradientGui = Instance.new("ScreenGui")
DeltaGradientGui.Name = "hooksense_DeltaGradientGui"
DeltaGradientGui.ResetOnSpawn = false
DeltaGradientGui.IgnoreGuiInset = true
DeltaGradientGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
DeltaGradientGui.Parent = TargetGuiParent

local FOVFillFrame = Instance.new("Frame")
FOVFillFrame.Name = "FOVGradientFrame"
FOVFillFrame.AnchorPoint = Vector2.new(0.5, 0.5)
FOVFillFrame.BorderSizePixel = 0
FOVFillFrame.BackgroundTransparency = 1
FOVFillFrame.Visible = false
FOVFillFrame.Parent = DeltaGradientGui

local FOVFillCorner = Instance.new("UICorner")
FOVFillCorner.CornerRadius = UDim.new(1, 0)
FOVFillCorner.Parent = FOVFillFrame

local FOVFillGradient = Instance.new("UIGradient")
FOVFillGradient.Parent = FOVFillFrame

local FOVCircleOutline = Drawing.new("Circle")
FOVCircleOutline.Thickness = 1.5
FOVCircleOutline.NumSides = 40
FOVCircleOutline.Filled = false
FOVCircleOutline.Visible = _G.FOVVisible

local FOVCircle = Drawing.new("Circle")
FOVCircle.Thickness = 1.0
FOVCircle.NumSides = 40
FOVCircle.Filled = false
FOVCircle.Visible = _G.FOVVisible

local TracerLineOutline = Drawing.new("Line")
TracerLineOutline.Transparency = 1.0

local TracerLine = Drawing.new("Line")
TracerLine.Transparency = 0.8

local function getScreenCenter()
    return Vector2.new(Camera.ViewportSize.X / 2, Camera.ViewportSize.Y / 2)
end

local function isBehindWall(targetPart)
    if not _G.WallCheckEnabled then return false end
    local Parts = Camera:GetPartsObscuringTarget({targetPart.Position}, {LocalPlayer.Character, targetPart.Parent})
    return #Parts > 0
end

local function isDead(humanoid, char)
    if not _G.DieCheckEnabled then return false end
    if humanoid and humanoid.Health <= 0 then return true end
    if char and not char:IsDescendantOf(workspace) then return true end
    return false
end

local CurrentAimTargetPosition = nil
local CurrentTargetPlayer = nil
local CurrentTargetCharacter = nil
local lastTarget = nil
local interpolationProgress = 0

task.spawn(function()
    while task.wait(0.01) do
        if not _G.SilentAimEnabled and not _G.MobileAimbotEnabled then
            CurrentAimTargetPosition = nil
            CurrentTargetPlayer = nil
            CurrentTargetCharacter = nil
            lastTarget = nil
            interpolationProgress = 0
        else
            local TempTargetChar = nil
            local TempPlayer = nil
            local MaxDistance = _G.FOVSize
            local Center = getScreenCenter()
            local MyRoot = LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
            local PotentialTargets = {}

            if _G.PermLockEnabled and #_G.PermTargetList > 0 then
                for _, pName in ipairs(_G.PermTargetList) do
                    local targetPlayerObject = Players:FindFirstChild(pName)
                    if targetPlayerObject and targetPlayerObject.Character then
                        local char = targetPlayerObject.Character
                        local rootPart = char:FindFirstChild("HumanoidRootPart")
                        local humanoid = char:FindFirstChildOfClass("Humanoid")
                        if rootPart and humanoid and not isDead(humanoid, char) then
                            if MyRoot and (rootPart.Position - MyRoot.Position).Magnitude <= _G.MaxTargetDistance then
                                if not isBehindWall(rootPart) then
                                    if not (_G.TeamCheckEnabled and targetPlayerObject.Team == LocalPlayer.Team) then
                                        TempTargetChar = char
                                        TempPlayer = targetPlayerObject
                                        break
                                    end
                                end
                            end
                        end
                    end
                end
            end

            if not TempTargetChar then
                for _, player in ipairs(Players:GetPlayers()) do
                    if player ~= LocalPlayer and player.Character then
                        table.insert(PotentialTargets, player.Character)
                    end
                end
                for _, char in ipairs(PotentialTargets) do
                    local rootPart = char:FindFirstChild("HumanoidRootPart")
                    local humanoid = char:FindFirstChildOfClass("Humanoid")
                    if rootPart and humanoid then
                        if isDead(humanoid, char) then continue end
                        if MyRoot and (rootPart.Position - MyRoot.Position).Magnitude > _G.MaxTargetDistance then continue end
                        if isBehindWall(rootPart) then continue end
                        local targetPlayerObject = Players:GetPlayerFromCharacter(char)
                        if _G.TeamCheckEnabled and targetPlayerObject and targetPlayerObject.Team == LocalPlayer.Team then continue end
                        local ScreenPosition, OnScreen = Camera:WorldToViewportPoint(rootPart.Position)
                        if OnScreen then
                            local DistanceToCenter = (Vector2.new(ScreenPosition.X, ScreenPosition.Y) - Center).Magnitude
                            if DistanceToCenter < MaxDistance then
                                TempTargetChar = char
                                TempPlayer = targetPlayerObject
                                MaxDistance = DistanceToCenter
                            end
                        end
                    end
                end
            end

            CurrentTargetPlayer = TempPlayer
            CurrentTargetCharacter = TempTargetChar

            if TempTargetChar then
                local targetPartName = _G.MobileAimbotEnabled and _G.AimbotTargetPart or _G.TargetPartMode
                local head = TempTargetChar:FindFirstChild("Head")
                local root = TempTargetChar:FindFirstChild("HumanoidRootPart")
                local targetPartObj = TempTargetChar:FindFirstChild(targetPartName) or head or root
                if targetPartObj then
                    local basePosition = targetPartObj.Position
                    if _G.AutoPredictionEnabled and root then
                        local ping = LocalPlayer:GetNetworkPing()
                        basePosition = basePosition + (root.Velocity * ping * _G.PredictionValue)
                    end
                    if _G.TargetPartMode == "Root to Head" and not _G.MobileAimbotEnabled then
                        if lastTarget ~= TempTargetChar then
                            lastTarget = TempTargetChar
                            interpolationProgress = 0
                        end
                        interpolationProgress = math.clamp(interpolationProgress + (0.01 * _G.TransitionSpeed), 0, 1)
                        CurrentAimTargetPosition = root.Position:Lerp(head.Position, interpolationProgress)
                    else
                        CurrentAimTargetPosition = basePosition
                        lastTarget = TempTargetChar
                    end
                else
                    CurrentAimTargetPosition = nil
                end
            else
                lastTarget = nil
                interpolationProgress = 0
                CurrentAimTargetPosition = nil
            end
        end
    end
end)

local CurrentConnectedHumanoid = nil
local HealthConnection = nil
local function BindHealthTracker(targetPlayer)
    if not targetPlayer or not targetPlayer.Character then return end
    local hum = targetPlayer.Character:FindFirstChildOfClass("Humanoid")
    if not hum then return end
    if CurrentConnectedHumanoid == hum then return end
    if HealthConnection then HealthConnection:Disconnect() end
    CurrentConnectedHumanoid = hum
    local lastHealth = hum.Health
    HealthConnection = hum:GetPropertyChangedSignal("Health"):Connect(function()
        if hum.Health < lastHealth then
            local damageCalculated = math.floor(lastHealth - hum.Health)
            task.spawn(PlayHitSound)
            task.spawn(TriggerHitOverlay) 
            local hitPartName = _G.TargetPartMode
            if hitPartName == "Root to Head" then
                hitPartName = "Body/Head"
            elseif hitPartName == "HumanoidRootPart" then
                hitPartName = "Torso"
            end
            task.spawn(ShowCustomHitNotification, targetPlayer.Name, hitPartName, damageCalculated)
        end
        lastHealth = hum.Health
    end)
end

local function CreateESP(player)
    local Billboard = Instance.new("BillboardGui")
    Billboard.Name = player.Name .. "_BillboardESP"
    Billboard.Size = UDim2.new(0, 200, 0, 50)
    Billboard.AlwaysOnTop = true
    Billboard.ExtentsOffset = Vector3.new(0, 2.5, 0)
    Billboard.Enabled = false
    Billboard.Parent = EspGui

    local NameLabel = Instance.new("TextLabel")
    NameLabel.Size = UDim2.new(1, 0, 0, 16)
    NameLabel.Font = _G.GlobalFontSetting
    NameLabel.TextSize = 13
    NameLabel.TextColor3 = _G.ColorName
    NameLabel.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
    NameLabel.TextStrokeTransparency = 0
    NameLabel.BackgroundTransparency = 1
    NameLabel.Parent = Billboard

    local HealthLabel = Instance.new("TextLabel")
    HealthLabel.Size = UDim2.new(1, 0, 0, 14)
    HealthLabel.Position = UDim2.new(0, 0, 0, 16)
    HealthLabel.Font = _G.GlobalFontSetting
    HealthLabel.TextSize = 12
    HealthLabel.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
    HealthLabel.TextStrokeTransparency = 0
    HealthLabel.BackgroundTransparency = 1
    HealthLabel.Parent = Billboard

    ESP_Storage[player] = {
        BillboardGui = Billboard,
        NameTag = NameLabel,
        HealthTag = HealthLabel
    }
end

local function RemoveESP(player)
    if ESP_Storage[player] then
        ESP_Storage[player].BillboardGui:Destroy()
        ESP_Storage[player] = nil
    end
    if player.Character then
        local highlight = player.Character:FindFirstChild("hooksenseHighlight")
        if highlight then highlight:Destroy() end
    end
end

for _, player in ipairs(Players:GetPlayers()) do
    if player ~= LocalPlayer then CreateESP(player) end
end
Players.PlayerAdded:Connect(function(player)
    if player ~= LocalPlayer then CreateESP(player) end
end)
Players.PlayerRemoving:Connect(function(player)
    RemoveESP(player)
end)

local RunService = game:GetService("RunService")
local spinAngle = 0
local jitterToggle = false
local LastLoggedHudTargetId = 0
local currentHudHealthLerp = 0 

RunService.RenderStepped:Connect(function()
    local Center = getScreenCenter()
    local ShowCircle = _G.FOVVisible and (_G.SilentAimEnabled or _G.MobileAimbotEnabled)
    
    FOVCircleOutline.Position = Center
    FOVCircleOutline.Radius = _G.FOVSize
    FOVCircleOutline.Visible = ShowCircle
    FOVCircleOutline.Color = _G.FOVCircleOutlineColor

    FOVCircle.Position = Center
    FOVCircle.Radius = _G.FOVSize
    FOVCircle.Visible = ShowCircle
    FOVCircle.Color = _G.FOVCircleColor

    if ShowCircle and _G.FOVFillEnabled then
        FOVFillFrame.Position = UDim2.new(0, Center.X, 0, Center.Y)
        FOVFillFrame.Size = UDim2.new(0, _G.FOVSize * 2, 0, _G.FOVSize * 2)
        
        FOVFillGradient.Color = ColorSequence.new({
            ColorSequenceKeypoint.new(0, _G.FOVFillColor1),
            ColorSequenceKeypoint.new(0.5, _G.FOVFillColor2),
            ColorSequenceKeypoint.new(1, _G.FOVFillColor3)
        })
        
        FOVFillFrame.BackgroundTransparency = _G.FOVFillTransparency
        
        if _G.FOVFillRotateEnabled then
            currentRotationAngle = (currentRotationAngle + (0.5 * _G.FOVFillRotateSpeed)) % 360
        end
        FOVFillGradient.Rotation = currentRotationAngle
        FOVFillFrame.Visible = true
    else
        FOVFillFrame.Visible = false
    end

    if (_G.SilentAimEnabled or _G.MobileAimbotEnabled) and _G.TracerEnabled and CurrentAimTargetPosition then
        local TargetPos, OnScreen = Camera:WorldToViewportPoint(CurrentAimTargetPosition)
        if OnScreen then
            local ToPos = Vector2.new(TargetPos.X, TargetPos.Y)
            TracerLineOutline.From = Center
            TracerLineOutline.To = ToPos
            TracerLineOutline.Visible = true
            TracerLineOutline.Color = _G.TracerLineOutlineColor
            TracerLineOutline.Thickness = _G.TracerOutlineThickness

            TracerLine.From = Center
            TracerLine.To = ToPos
            TracerLine.Visible = true
            TracerLine.Color = _G.TracerLineColor
            TracerLine.Thickness = _G.TracerThickness
        else
            TracerLineOutline.Visible = false
            TracerLine.Visible = false
        end
    else
        TracerLineOutline.Visible = false
        TracerLine.Visible = false
    end

    if _G.MobileAimbotEnabled and CurrentAimTargetPosition then
        local targetCFrame = CFrame.new(Camera.CFrame.Position, CurrentAimTargetPosition)
        Camera.CFrame = Camera.CFrame:Lerp(targetCFrame, _G.AimbotSmoothness)
    end

    if (_G.SilentAimEnabled or _G.MobileAimbotEnabled) and CurrentTargetPlayer and CurrentTargetPlayer.Character then
        local Hum = CurrentTargetPlayer.Character:FindFirstChildOfClass("Humanoid")
        if Hum then
            DisplayNameLabel.Text = CurrentTargetPlayer.DisplayName
            UsernameLabel.Text = "@" .. CurrentTargetPlayer.Name
            UserIdLabel.Text = "USER ID: " .. tostring(CurrentTargetPlayer.UserId)
            
            local pct = math.clamp(Hum.Health / Hum.MaxHealth, 0, 1)
            
            if CurrentTargetPlayer.UserId ~= LastLoggedHudTargetId then
                currentHudHealthLerp = pct
                LastLoggedHudTargetId = CurrentTargetPlayer.UserId
                AvatarImage.Image = "rbxthumb://type=AvatarHeadShot&id=" .. tostring(CurrentTargetPlayer.UserId) .. "&w=150&h=150"
            end
            
            currentHudHealthLerp = currentHudHealthLerp + (pct - currentHudHealthLerp) * 0.12
            HealthBar.Size = UDim2.new(currentHudHealthLerp, 0, 1, 0)
            HealthBar.BackgroundColor3 = Color3.fromHSV(currentHudHealthLerp * 0.38, 0.9, 1)
            
            BindHealthTracker(CurrentTargetPlayer)
            ToggleHUD(true)
        else
            ToggleHUD(false)
            LastLoggedHudTargetId = 0
        end
    else
        ToggleHUD(false)
        LastLoggedHudTargetId = 0
    end

    if _G.SilentAimEnabled and _G.LookAtEnabled and LocalPlayer.Character then
        local Root = LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
        local Humanoid = LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
        if Root and Humanoid and Humanoid.Health > 0 and not _G.AntiAimEnabled then
            if CurrentAimTargetPosition then
                Humanoid.AutoRotate = false
                local lookVector = Vector3.new(CurrentAimTargetPosition.X, Root.Position.Y, CurrentAimTargetPosition.Z)
                Root.CFrame = CFrame.lookAt(Root.Position, lookVector)
            else
                Humanoid.AutoRotate = true
            end
        end
    end

    if _G.AntiAimEnabled and LocalPlayer.Character then
        local Root = LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
        local Humanoid = LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
        if Root and Humanoid and Humanoid.Health > 0 then
            Humanoid.AutoRotate = false
            if _G.AntiAimMode == "Spin" then
                spinAngle = (spinAngle + _G.AntiAimSpeed) % 360
                Root.CFrame = CFrame.new(Root.Position) * CFrame.Angles(0, math.rad(spinAngle), 0)
            elseif _G.AntiAimMode == "Jitter" then
                local intensity = 1
                if _G.JitterMode == "Multi" then intensity = math.random(1, 5)
                elseif _G.JitterMode == "5x always" then intensity = 5
                elseif _G.JitterMode == "3x always" then intensity = 3
                elseif _G.JitterMode == "2x always" then intensity = 2
                elseif _G.JitterMode == "random" then intensity = math.random(1, 5)
                else intensity = math.random(1, 5) end
                jitterToggle = not jitterToggle
                local _, cameraY, _ = Camera.CFrame:ToOrientation()
                local jitterOffset = jitterToggle and math.rad(22.5 * intensity) or math.rad(-22.5 * intensity)
                Root.CFrame = CFrame.new(Root.Position) * CFrame.Angles(0, cameraY + jitterOffset, 0)
                local LowerTorso = LocalPlayer.Character:FindFirstChild("LowerTorso") or LocalPlayer.Character:FindFirstChild("Torso")
                if LowerTorso and LowerTorso:FindFirstChild("RootJoint") then
                    LowerTorso.RootJoint.Transform = CFrame.Angles(0, jitterOffset, 0)
                end
            end
        end
    else
        if LocalPlayer.Character then
            local Humanoid = LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
            if Humanoid then
                if not _G.LookAtEnabled or (_G.LookAtEnabled and not CurrentAimTargetPosition) then
                    Humanoid.AutoRotate = true
                end
            end
            local LowerTorso = LocalPlayer.Character:FindFirstChild("LowerTorso") or LocalPlayer.Character:FindFirstChild("Torso")
            if LowerTorso and LowerTorso:FindFirstChild("RootJoint") then
                LowerTorso.RootJoint.Transform = CFrame.new()
            end
        end
    end

    if _G.ThirdPersonEnabled and LocalPlayer.Character then
        LocalPlayer.CameraMode = Enum.CameraMode.Classic
        for _, obj in ipairs(LocalPlayer.Character:GetDescendants()) do
            if obj:IsA("BasePart") and obj.Name ~= "HumanoidRootPart" then
                obj.LocalTransparencyModifier = 0
            end
        end
        local cameraRotation = Camera.CFrame - Camera.CFrame.Position
        local targetCameraPosition = Camera.Focus.Position - (Camera.CFrame.LookVector * _G.ThirdPersonDistance)
        Camera.CFrame = cameraRotation + targetCameraPosition
    end

    for player, v in pairs(ESP_Storage) do
        local char = player.Character
        local head = char and char:FindFirstChild("Head")
        local hrp = char and char:FindFirstChild("HumanoidRootPart")
        local humanoid = char and char:FindFirstChildOfClass("Humanoid")
        
        -- แก้ไขจุดนี้: แก้ไวยากรณ์ผิดพลาด นำตัวแปรแปลกปลอมออก
        if _G.ESPEnabled and char and head and hrp and humanoid and humanoid.Health > 0 then
            if _G.TeamCheckEnabled and player.Team == LocalPlayer.Team then
                local highlight = char:FindFirstChild("hooksenseHighlight")
                if highlight then highlight.Enabled = false end
                v.BillboardGui.Enabled = false
                continue
            end
            local highlight = char:FindFirstChild("hooksenseHighlight")
            if _G.ESPHighlights then
                if not highlight then
                    highlight = Instance.new("Highlight")
                    highlight.Name = "hooksenseHighlight"
                    highlight.Parent = char
                end
                highlight.FillColor = _G.ColorBox
                highlight.FillTransparency = 0.5
                highlight.OutlineColor = Color3.fromRGB(0, 0, 0)
                highlight.OutlineTransparency = 0
                highlight.Enabled = true
            else
                if highlight then highlight.Enabled = false end
            end

            if v.BillboardGui.Adornee ~= head then v.BillboardGui.Adornee = head end
            local _, OnScreen = Camera:WorldToViewportPoint(head.Position)
            if OnScreen then
                v.BillboardGui.Enabled = true
                local Distance = (Camera.CFrame.Position - hrp.Position).Magnitude
                v.NameTag.Text = player.Name .. " [" .. math.floor(Distance) .. "m]"
                v.NameTag.TextColor3 = _G.ColorName
                v.NameTag.Visible = _G.ESPName
                if _G.ESPHealth then
                    local currentHealth = math.floor(humanoid.Health)
                    local HealthPercentage = currentHealth / humanoid.MaxHealth
                    local healthColor = HealthPercentage > 0.6 and Color3.fromRGB(0, 255, 120) or (HealthPercentage > 0.3 and Color3.fromRGB(255, 215, 0) or Color3.fromRGB(255, 50, 50))
                    v.HealthTag.Text = "HP: " .. currentHealth
                    v.HealthTag.TextColor3 = healthColor
                    v.HealthTag.Visible = true
                else
                    v.HealthTag.Visible = false
                end
                continue
            end
        else
            local highlight = char and char:FindFirstChild("hooksenseHighlight")
            if highlight then highlight.Enabled = false end
        end
        v.BillboardGui.Enabled = false
    end
end)

task.spawn(function()
    while true do
        task.wait()
        if _G.BhopEnabled and LocalPlayer.Character then
            local Humanoid = LocalPlayer.Character:FindFirstChildOfClass("Humanoid")
            local Root = LocalPlayer.Character:FindFirstChild("HumanoidRootPart")
            if Humanoid and Root then
                local MoveDirection = Humanoid.MoveDirection
                if MoveDirection.Magnitude > 0 then
                    if Humanoid.FloorMaterial ~= Enum.Material.Air then
                        Humanoid:ChangeState(Enum.HumanoidStateType.Jumping)
                    end
                    Root.Velocity = Vector3.new(MoveDirection.X * (Humanoid.WalkSpeed * _G.BhopSpeedMultiplier), Root.Velocity.Y, MoveDirection.Z * (Humanoid.WalkSpeed * _G.BhopSpeedMultiplier))
                end
            end
        end
    end
end)

local OldNamecall
OldNamecall = hookmetamethod(game, "__namecall", newcclosure(function(Self, ...)
    if checkcaller() then return OldNamecall(Self, ...) end
    local Args = { ... }
    local Method = getnamecallmethod()
    local SelfClass = ""
    pcall(function()
        if Self and typeof(Self) == "Instance" then SelfClass = Self.ClassName end
    end)

    if _G.SilentAimEnabled and CurrentAimTargetPosition then
        if (Method == "ScreenPointToRay" or Method == "ViewportPointToRay") and SelfClass == "Camera" then
            return Ray.new(Camera.CFrame.Position, (CurrentAimTargetPosition - Camera.CFrame.Position).Unit)
        end
        if Method == "Raycast" and SelfClass == "Workspace" then
            if _G.BulletTPEnabled then
                Args[1] = CurrentAimTargetPosition - (Args[2].Unit * 1)
                Args[2] = Args[2].Unit * 5
            else
                Args[2] = (CurrentAimTargetPosition - Args[1]).Unit * Args[2].Magnitude
            end
            return OldNamecall(Self, table.unpack(Args))
        end
        if (Method == "FindPartOnRay" or Method == "FindPartOnRayWithIgnoreList" or Method == "FindPartOnRayWithWhitelist") and SelfClass == "Workspace" then
            local CurrentRay = Args[1]
            if CurrentRay and typeof(CurrentRay) == "Ray" then
                if _G.BulletTPEnabled then
                    local NewOrigin = CurrentAimTargetPosition - (CurrentRay.Direction.Unit * 1)
                    Args[1] = Ray.new(NewOrigin, CurrentRay.Direction.Unit * 5)
                else
                    Args[1] = Ray.new(CurrentRay.Origin, (CurrentAimTargetPosition - CurrentRay.Origin).Unit * CurrentRay.Direction.Magnitude)
                end
                return OldNamecall(Self, table.unpack(Args))
            end
        end
    end
    return OldNamecall(Self, ...)
end))

local Tabs = {
    Main = Window:AddTab("Main"),
    Aimbot = Window:AddTab("Aimbot"),
    HitEffects = Window:AddTab("Hits"),
    ESP = Window:AddTab("Esp"),
    Movement = Window:AddTab("Character"),
    World = Window:AddTab("World"),
    Addons = Window:AddTab("Addons"),
    ['UI'] = Window:AddTab("Setting")
}

local Options = getgenv().Options
local Toggles = getgenv().Toggles

local MobileAimbotBox = Tabs.Aimbot:AddLeftGroupbox("Aimbot")
local MobileAimbotSettings = Tabs.Aimbot:AddRightGroupbox("Aimbot Options")

MobileAimbotBox:AddToggle("MobileAimbotToggle", { Text = "Enable Aimbot", Default = false })
    :AddKeyPicker("MobileAimbotKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Mobile Aimbot Bind" })

Toggles.MobileAimbotToggle:OnChanged(function()
    _G.MobileAimbotEnabled = Toggles.MobileAimbotToggle.Value
end)

MobileAimbotBox:AddSlider("AimbotSmoothSlider", { Text = "Aimbot Smoothness", Default = 0.1, Min = 0.01, Max = 1, Rounding = 2 })
Options.AimbotSmoothSlider:OnChanged(function()
    _G.AimbotSmoothness = Options.AimbotSmoothSlider.Value
end)

MobileAimbotBox:AddSlider("JumpSmoothSlider", { Text = "Jump Smooth", Default = 1, Min = 1, Max = 100, Rounding = 0, Suffix = "%" })
Options.JumpSmoothSlider:OnChanged(function()
    _G.JumpSmooth = Options.JumpSmoothSlider.Value
end)

MobileAimbotBox:AddSlider("SmoothXSlider", { Text = "Smooth X", Default = 1, Min = 1, Max = 100, Rounding = 0, Suffix = "%" })
Options.SmoothXSlider:OnChanged(function()
    _G.SmoothX = Options.SmoothXSlider.Value
end)

MobileAimbotBox:AddSlider("SmoothZSlider", { Text = "Smooth Z", Default = 1, Min = 1, Max = 100, Rounding = 0, Suffix = "%" })
Options.SmoothZSlider:OnChanged(function()
    _G.SmoothZ = Options.SmoothZSlider.Value
end)

MobileAimbotBox:AddToggle("AutoPredictionToggle", { Text = "Enable Auto Prediction", Default = false })
Toggles.AutoPredictionToggle:OnChanged(function()
    _G.AutoPredictionEnabled = Toggles.AutoPredictionToggle.Value
end)

MobileAimbotBox:AddSlider("PredictionSlider", { Text = "Prediction Multiplier", Default = 0.1, Min = 0.0, Max = 5.0, Rounding = 2 })
Options.PredictionSlider:OnChanged(function()
    _G.PredictionValue = Options.PredictionSlider.Value
end)

MobileAimbotSettings:AddDropdown("MobileTargetPartDropdown", { Text = "Aimbot Target Part", Values = {"Head", "HumanoidRootPart"}, Default = 1, Multi = false })
Options.MobileTargetPartDropdown:OnChanged(function()
    _G.AimbotTargetPart = Options.MobileTargetPartDropdown.Value
end)

local LeftGroupBox = Tabs.Main:AddLeftGroupbox("Silent Aim")
local PermLockGroupBox = Tabs.Main:AddLeftGroupbox("Permanent Lock Settings")
local TargetGroupBox = Tabs.Main:AddLeftGroupbox("Targeting Options")
local FOVGroupBox = Tabs.Main:AddRightGroupbox("FOV Settings")
local FOVFillGroupBox = Tabs.Main:AddRightGroupbox("FOV Dynamic Gradient Fill")
local TracerGroupBox = Tabs.Main:AddRightGroupbox("Tracer Line Settings")

LeftGroupBox:AddToggle("SilentAimToggle", { Text = "Enable Silent Aim", Default = false })
    :AddKeyPicker("SilentAimKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Silent Aim Bind" })

Toggles.SilentAimToggle:OnChanged(function()
    _G.SilentAimEnabled = Toggles.SilentAimToggle.Value
end)

LeftGroupBox:AddToggle("LookAtToggle", { Text = "Enable Look at Target", Default = false })
    :AddKeyPicker("LookAtKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Look At Bind" })

Toggles.LookAtToggle:OnChanged(function()
    _G.LookAtEnabled = Toggles.LookAtToggle.Value
end)

LeftGroupBox:AddToggle("BulletTPToggle", { Text = "Enable Bullet TP", Default = false })
    :AddKeyPicker("BulletTPKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Bullet TP Bind" })

Toggles.BulletTPToggle:OnChanged(function()
    _G.BulletTPEnabled = Toggles.BulletTPToggle.Value
end)

LeftGroupBox:AddToggle("WallCheckToggle", { Text = "Enable Wall Check", Default = false })
Toggles.WallCheckToggle:OnChanged(function()
    _G.WallCheckEnabled = Toggles.WallCheckToggle.Value
end)

LeftGroupBox:AddToggle("TeamCheckToggle", { Text = "Enable Team Check", Default = false })
Toggles.TeamCheckToggle:OnChanged(function()
    _G.TeamCheckEnabled = Toggles.TeamCheckToggle.Value
end)

PermLockGroupBox:AddToggle("PermLockToggle", { Text = "Enable Perm Lock-On", Default = false })
    :AddKeyPicker("PermLockKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Perm Lock Bind" })

Toggles.PermLockToggle:OnChanged(function()
    _G.PermLockEnabled = Toggles.PermLockToggle.Value
end)

PermLockGroupBox:AddDropdown("PermTargetDropdown", { Text = "Targets Queue List", Values = {"No Targets Added"}, Default = 1, Multi = false })

local function RefreshDropdownValues()
    if #_G.PermTargetList == 0 then
        Options.PermTargetDropdown:SetValues({"No Targets Added"})
        Options.PermTargetDropdown:SetValue(1)
    else
        for i = #_G.PermTargetList, 1, -1 do
            if not Players:FindFirstChild(_G.PermTargetList[i]) then
                table.remove(_G.PermTargetList, i)
            end
        end
        if #_G.PermTargetList == 0 then
            Options.PermTargetDropdown:SetValues({"No Targets Added"})
            Options.PermTargetDropdown:SetValue(1)
        else
            Options.PermTargetDropdown:SetValues(_G.PermTargetList)
            Options.PermTargetDropdown:SetValue(_G.PermTargetList[1])
        end
    end
end

Players.PlayerRemoving:Connect(function()
    task.wait(0.1)
    RefreshDropdownValues()
end)
Players.PlayerAdded:Connect(function()
    task.wait(0.1)
    RefreshDropdownValues()
end)

PermLockGroupBox:AddButton({Text = "Clear All Targets", Func = function()
    _G.PermTargetList = {}
    RefreshDropdownValues()
    Library:Notify("Permanent Target List Cleared!")
end})

PermLockGroupBox:AddInput("PermTargetInput", { Placeholder = "Enter Display or Username...", Text = "", Numeric = false, Finished = false, })
PermLockGroupBox:AddButton({Text = "Target Player", Func = function()
    local enteredText = Options.PermTargetInput.Value
    if enteredText and enteredText ~= "" then
        enteredText = string.gsub(enteredText, "%s+", "")
        local matchFound = nil
        for _, p in ipairs(Players:GetPlayers()) do
            local nameMatch = string.find(string.lower(p.Name), string.lower(enteredText))
            local dispMatch = string.find(string.lower(p.DisplayName), string.lower(enteredText))
            if nameMatch or dispMatch then
                matchFound = p.Name
                break
            end
        end
        if matchFound then
            if not table.find(_G.PermTargetList, matchFound) then
                table.insert(_G.PermTargetList, matchFound)
                RefreshDropdownValues()
                Options.PermTargetDropdown:SetValue(matchFound)
                Library:Notify("Successfully Targeted: " .. matchFound)
            else
                Library:Notify("Player already exists in list!")
            end
        else
            Library:Notify("No matching player found on this server!")
        end
        Options.PermTargetInput:SetValue("")
    else
        Library:Notify("Please enter a valid player name.")
    end
end})

TargetGroupBox:AddDropdown("TargetPartDropdown", { Text = "Target Lock Part", Values = {"Head", "HumanoidRootPart", "Root to Head"}, Default = 1, Multi = false })
Options.TargetPartDropdown:OnChanged(function()
    _G.TargetPartMode = Options.TargetPartDropdown.Value
end)

TargetGroupBox:AddSlider("TransitionSpeedSlider", { Text = "Root Transfer Speed (Root to Head)", Default = 5, Min = 1, Max = 30, Rounding = 1 })
Options.TransitionSpeedSlider:OnChanged(function()
    _G.TransitionSpeed = Options.TransitionSpeedSlider.Value
end)

TargetGroupBox:AddSlider("MaxDistanceSlider", { Text = "Max Lock Distance (Studs)", Default = 10000, Min = 1, Max = 100000, Rounding = 0 })
Options.MaxDistanceSlider:OnChanged(function()
    _G.MaxTargetDistance = Options.MaxDistanceSlider.Value
end)

FOVGroupBox:AddToggle("FOVVisibleToggle", { Text = "Show FOV Circle", Default = true })
Toggles.FOVVisibleToggle:OnChanged(function()
    _G.FOVVisible = Toggles.FOVVisibleToggle.Value
end)

FOVGroupBox:AddSlider("FOVSlider", { Text = "FOV Size Radius", Default = 100, Min = 40, Max = 800, Rounding = 0 })
Options.FOVSlider:OnChanged(function()
    _G.FOVSize = Options.FOVSlider.Value
end)

FOVGroupBox:AddLabel("FOV Line Color"):AddColorPicker("FOVCircleColorPicker", { Default = Color3.fromRGB(255, 255, 255) })
Options.FOVCircleColorPicker:OnChanged(function()
    _G.FOVCircleColor = Options.FOVCircleColorPicker.Value
end)

FOVGroupBox:AddLabel("FOV Outline Color"):AddColorPicker("FOVCircleOutlineColorPicker", { Default = Color3.fromRGB(0, 0, 0) })
Options.FOVCircleOutlineColorPicker:OnChanged(function()
    _G.FOVCircleOutlineColor = Options.FOVCircleOutlineColorPicker.Value
end)

FOVFillGroupBox:AddToggle("FOVFillToggle", { Text = "Enable FOV Fill", Default = false })
Toggles.FOVFillToggle:OnChanged(function()
    _G.FOVFillEnabled = Toggles.FOVFillToggle.Value
end)

FOVFillGroupBox:AddSlider("FOVFillTransparencySlider", { Text = "FOV Fill Opacity", Default = 0.2, Min = 0, Max = 1, Rounding = 2 })
Options.FOVFillTransparencySlider:OnChanged(function()
    _G.FOVFillTransparency = Options.FOVFillTransparencySlider.Value
end)

FOVFillGroupBox:AddLabel("Fill Color 1 (Top)"):AddColorPicker("FOVFillColor1Picker", { Default = Color3.fromRGB(255, 0, 0) })
Options.FOVFillColor1Picker:OnChanged(function()
    _G.FOVFillColor1 = Options.FOVFillColor1Picker.Value
end)

FOVFillGroupBox:AddLabel("Fill Color 2 (Mid)"):AddColorPicker("FOVFillColor2Picker", { Default = Color3.fromRGB(0, 255, 0) })
Options.FOVFillColor2Picker:OnChanged(function()
    _G.FOVFillColor2 = Options.FOVFillColor2Picker.Value
end)

FOVFillGroupBox:AddLabel("Fill Color 3 (Bottom)"):AddColorPicker("FOVFillColor3Picker", { Default = Color3.fromRGB(0, 0, 255) })
Options.FOVFillColor3Picker:OnChanged(function()
    _G.FOVFillColor3 = Options.FOVFillColor3Picker.Value
end)

FOVFillGroupBox:AddToggle("FOVFillRotateToggle", { Text = "Rotate FOV Gradient", Default = false })
Toggles.FOVFillRotateToggle:OnChanged(function()
    _G.FOVFillRotateEnabled = Toggles.FOVFillRotateToggle.Value
end)

FOVFillGroupBox:AddSlider("FOVFillRotateSpeedSlider", { Text = "Gradient Rotation Speed", Default = 1, Min = 1, Max = 10, Rounding = 1 })
Options.FOVFillRotateSpeedSlider:OnChanged(function()
    _G.FOVFillRotateSpeed = Options.FOVFillRotateSpeedSlider.Value
end)

TracerGroupBox:AddToggle("TracerVisibleToggle", { Text = "Enable Tracer Line", Default = true })
Toggles.TracerVisibleToggle:OnChanged(function()
    _G.TracerEnabled = Toggles.TracerVisibleToggle.Value
end)

TracerGroupBox:AddSlider("TracerThicknessSlider", { Text = "Tracer Line Thickness", Default = 1.0, Min = 0.5, Max = 5.0, Rounding = 1 })
Options.TracerThicknessSlider:OnChanged(function()
    _G.TracerThickness = Options.TracerThicknessSlider.Value
end)

TracerGroupBox:AddSlider("TracerOutlineThicknessSlider", { Text = "Tracer Outline Thickness", Default = 3.0, Min = 1.0, Max = 8.0, Rounding = 1 })
Options.TracerOutlineThicknessSlider:OnChanged(function()
    _G.TracerOutlineThickness = Options.TracerOutlineThicknessSlider.Value
end)

TracerGroupBox:AddLabel("Tracer Main Color"):AddColorPicker("TracerLineColorPicker", { Default = Color3.fromRGB(255, 0, 0) })
Options.TracerLineColorPicker:OnChanged(function()
    _G.TracerLineColor = Options.TracerLineColorPicker.Value
end)

TracerGroupBox:AddLabel("Tracer Outline Color"):AddColorPicker("TracerLineOutlineColorPicker", { Default = Color3.fromRGB(0, 0, 0) })
Options.TracerLineOutlineColorPicker:OnChanged(function()
    _G.TracerLineOutlineColor = Options.TracerLineOutlineColorPicker.Value
end)

local SoundLeftBox = Tabs.HitEffects:AddLeftGroupbox("Hit Sound")
local OverlayLeftBox = Tabs.HitEffects:AddLeftGroupbox("Hit Overlay") 
local NotifyRightBox = Tabs.HitEffects:AddRightGroupbox("Hit Notification")

SoundLeftBox:AddDropdown("HitSoundDropdown", { Text = "Target Hit Sound", Values = {"None", "Spark", "Neverlose", "Rust", "Fatality", "Fatality 2", "Minecraft xp", "Minecraft", "Skeet"}, Default = 1, Multi = false })
Options.HitSoundDropdown:OnChanged(function()
    _G.HitSoundMode = Options.HitSoundDropdown.Value
end)

SoundLeftBox:AddSlider("HitSoundVolumeSlider", { Text = "Hit Sound Volume Level", Default = 2.0, Min = 0.0, Max = 5.0, Rounding = 1 })
Options.HitSoundVolumeSlider:OnChanged(function()
    _G.HitSoundVolume = Options.HitSoundVolumeSlider.Value
end)

OverlayLeftBox:AddToggle("HitOverlayToggle", { Text = "Enable Hit Overlay", Default = false })
Toggles.HitOverlayToggle:OnChanged(function()
    _G.HitOverlayEnabled = Toggles.HitOverlayToggle.Value
end)

OverlayLeftBox:AddLabel("Overlay Border Color"):AddColorPicker("HitOverlayColorPicker", { Default = Color3.fromRGB(255, 0, 0) })
Options.HitOverlayColorPicker:OnChanged(function()
    _G.HitOverlayColor = Options.HitOverlayColorPicker.Value
end)

NotifyRightBox:AddToggle("HitNotifyToggle", { Text = "Enable Hit Notification (With Checkmark ✓)", Default = true })
Toggles.HitNotifyToggle:OnChanged(function()
    _G.HitNotifyEnabled = Toggles.HitNotifyToggle.Value
end)

NotifyRightBox:AddDropdown("HitNotifyStyleDropdown", { Text = "Notify Screen Alignment", Values = {"Left", "Right", "Center"}, Default = 2, Multi = false })
Options.HitNotifyStyleDropdown:OnChanged(function()
    _G.HitNotifyStyle = Options.HitNotifyStyleDropdown.Value
end)

NotifyRightBox:AddDropdown("HitNotifyAnimDropdown", { Text = "Open Animation Engine", Values = {"Smooth", "Tween Inside"}, Default = 1, Multi = false })
Options.HitNotifyAnimDropdown:OnChanged(function()
    _G.HitNotifyAnimType = Options.HitNotifyAnimDropdown.Value
end)

NotifyRightBox:AddSlider("HitNotifyTransparencySlider", { Text = "Box Transparency Override", Default = 0.0, Min = 0.0, Max = 0.9, Rounding = 2 })
Options.HitNotifyTransparencySlider:OnChanged(function()
    _G.HitNotifyTransparency = Options.HitNotifyTransparencySlider.Value
end)

NotifyRightBox:AddSlider("HitNotifyPosXSlider", { Text = "Manual Position X (%)", Default = 50, Min = 0, Max = 100, Rounding = 0 })
Options.HitNotifyPosXSlider:OnChanged(function()
    _G.HitNotifyPosX = Options.HitNotifyPosXSlider.Value
end)

NotifyRightBox:AddSlider("HitNotifyPosYSlider", { Text = "Manual Position Y (%)", Default = 80, Min = 0, Max = 100, Rounding = 0 })
Options.HitNotifyPosYSlider:OnChanged(function()
    _G.HitNotifyPosY = Options.HitNotifyPosYSlider.Value
end)

NotifyRightBox:AddSlider("HitNotifyDurationSlider", { Text = "Stay Screen Duration", Default = 2.5, Min = 0.2, Max = 3.0, Rounding = 1 })
Options.HitNotifyDurationSlider:OnChanged(function()
    _G.HitNotifyDuration = Options.HitNotifyDurationSlider.Value
end)

NotifyRightBox:AddLabel("Notify Stroke Glow Color"):AddColorPicker("HitNotifyColorPicker", { Default = Color3.fromRGB(0, 255, 255) })
Options.HitNotifyColorPicker:OnChanged(function()
    _G.HitNotifyColor = Options.HitNotifyColorPicker.Value
    for _, frame in ipairs(ActiveNotifications) do
        local strokeObj = frame:FindFirstChildOfClass("UIStroke")
        if strokeObj then strokeObj.Color = _G.HitNotifyColor end
        local checkmarkObj = frame:FindFirstChild("CheckmarkIcon")
        if checkmarkObj then checkmarkObj.TextColor3 = _G.HitNotifyColor end
    end
end)

local EspLeftBox = Tabs.ESP:AddLeftGroupbox("Master Visuals Control")
local EspRightBox = Tabs.ESP:AddRightGroupbox("Visual Color Customization")

EspLeftBox:AddToggle("MasterESPToggle", { Text = "Enable ESP", Default = false })
    :AddKeyPicker("MasterESPKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Master ESP Bind" })

Toggles.MasterESPToggle:OnChanged(function()
    _G.ESPEnabled = Toggles.MasterESPToggle.Value
end)

EspLeftBox:AddToggle("NameESPToggle", { Text = "Player Name ESP", Default = false })
Toggles.NameESPToggle:OnChanged(function()
    _G.ESPName = Toggles.NameESPToggle.Value
end)

EspLeftBox:AddToggle("ChamsESPToggle", { Text = "Chams / Highlights ESP", Default = false })
Toggles.ChamsESPToggle:OnChanged(function()
    _G.ESPHighlights = Toggles.ChamsESPToggle.Value
end)

EspLeftBox:AddToggle("HealthESPToggle", { Text = "Health Text ESP", Default = false })
Toggles.HealthESPToggle:OnChanged(function()
    _G.ESPHealth = Toggles.HealthESPToggle.Value
end)

EspRightBox:AddLabel("Highlight Glow Color"):AddColorPicker("GlowColorPicker", { Default = Color3.fromRGB(0, 255, 255) })
Options.GlowColorPicker:OnChanged(function()
    _G.ColorBox = Options.GlowColorPicker.Value
end)

EspRightBox:AddLabel("Name Text Color"):AddColorPicker("NameColorPicker", { Default = Color3.fromRGB(255, 255, 255) })
Options.NameColorPicker:OnChanged(function()
    _G.ColorName = Options.NameColorPicker.Value
end)

local MoveLeftBox = Tabs.Movement:AddLeftGroupbox("Anti Aim")
local MoveRightBox = Tabs.Movement:AddRightGroupbox("Movement & Camera")

MoveLeftBox:AddToggle("AntiAimToggle", { Text = "Enable Anti Aim", Default = false })
    :AddKeyPicker("AntiAimKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Anti Aim Bind" })

Toggles.AntiAimToggle:OnChanged(function()
    _G.AntiAimEnabled = Toggles.AntiAimToggle.Value
end)

MoveLeftBox:AddDropdown("AntiAimModeDropdown", { Text = "Anti Aim Stance Type", Values = {"Spin", "Jitter"}, Default = 1, Multi = false })
Options.AntiAimModeDropdown:OnChanged(function()
    _G.AntiAimMode = Options.AntiAimModeDropdown.Value
end)

MoveLeftBox:AddDropdown("JitterSettingDropdown", { Text = "Jitter Core Settings", Values = {"Multi", "5x always", "3x always", "2x always", "random"}, Default = 1, Multi = false })
Options.JitterSettingDropdown:OnChanged(function()
    _G.JitterMode = Options.JitterSettingDropdown.Value
end)

MoveLeftBox:AddSlider("SpinSpeedSlider", { Text = "Rotation Spin Speed", Default = 15, Min = 5, Max = 50, Rounding = 0 })
Options.SpinSpeedSlider:OnChanged(function()
    _G.AntiAimSpeed = Options.SpinSpeedSlider.Value
end)

MoveRightBox:AddToggle("ThirdPersonToggle", { Text = "Enable Third Person View", Default = false })
    :AddKeyPicker("ThirdPersonKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Third Person Bind" })

Toggles.ThirdPersonToggle:OnChanged(function()
    _G.ThirdPersonEnabled = Toggles.ThirdPersonToggle.Value
end)

MoveRightBox:AddSlider("ThirdPersonDistanceSlider", { Text = "Third Person Distance Modifier", Default = 12, Min = 5, Max = 30, Rounding = 0 })
Options.ThirdPersonDistanceSlider:OnChanged(function()
    _G.ThirdPersonDistance = Options.ThirdPersonDistanceSlider.Value
end)

MoveRightBox:AddToggle("BhopToggle", { Text = "Enable Auto Bunny Hop", Default = false })
    :AddKeyPicker("BhopKeybind", { Default = "None", SyncToggleState = true, Mode = "Toggle", Text = "Bhop Bind" })

Toggles.BhopToggle:OnChanged(function()
    _G.BhopEnabled = Toggles.BhopToggle.Value
end)

MoveRightBox:AddSlider("BhopMultiplierSlider", { Text = "Bhop Velocity Speed Multiplier", Default = 1.5, Min = 1, Max = 5, Rounding = 1 })
Options.BhopMultiplierSlider:OnChanged(function()
    _G.BhopSpeedMultiplier = Options.BhopMultiplierSlider.Value
end)

local LightingColorsGroup = Tabs.World:AddLeftGroupbox("Lighting Colors & Time")
local WorldSkyboxBox = Tabs.World:AddLeftGroupbox("Custom Skybox System")
local WorldFogBox = Tabs.World:AddLeftGroupbox("Fog Customization")
local WorldRightBox = Tabs.World:AddRightGroupbox("Weather Modifier Engine")

LightingColorsGroup:AddSlider("ClockTimeSlider", { Text = "Game Clock Time", Default = Lighting.ClockTime, Min = 0, Max = 24, Rounding = 1 })
Options.ClockTimeSlider:OnChanged(function()
    Lighting.ClockTime = Options.ClockTimeSlider.Value
end)

LightingColorsGroup:AddLabel("Ambient Color"):AddColorPicker("AmbientColorPicker", { Default = Lighting.Ambient })
Options.AmbientColorPicker:OnChanged(function()
    Lighting.Ambient = Options.AmbientColorPicker.Value
end)

LightingColorsGroup:AddLabel("Outdoor Ambient Color"):AddColorPicker("OutdoorAmbientColorPicker", { Default = Lighting.OutdoorAmbient })
Options.OutdoorAmbientColorPicker:OnChanged(function()
    Lighting.OutdoorAmbient = Options.OutdoorAmbientColorPicker.Value
end)

LightingColorsGroup:AddLabel("ColorShift Top Color"):AddColorPicker("ColorShiftTopColorPicker", { Default = Lighting.ColorShift_Top })
Options.ColorShiftTopColorPicker:OnChanged(function()
    Lighting.ColorShift_Top = Options.ColorShiftTopColorPicker.Value
end)

LightingColorsGroup:AddLabel("ColorShift Bottom Color"):AddColorPicker("ColorShiftBottomColorPicker", { Default = Lighting.ColorShift_Bottom })
Options.ColorShiftBottomColorPicker:OnChanged(function()
    Lighting.ColorShift_Bottom = Options.ColorShiftBottomColorPicker.Value
end)

WorldSkyboxBox:AddToggle("SkyboxToggle", { Text = "Enable Custom Skybox", Default = false })
Toggles.SkyboxToggle:OnChanged(function()
    _G.SkyboxEnabled = Toggles.SkyboxToggle.Value
    UpdateSkybox()
end)

WorldSkyboxBox:AddDropdown("SkyboxDropdown", { Text = "Select Skybox Type", Values = {"Minecraft", "Minecraft 2", "Skyblox 1", "Skyblox 2", "Skyblox 3", "Skyblox 4"}, Default = 1, Multi = false })
Options.SkyboxDropdown:OnChanged(function()
    _G.SelectedSkybox = Options.SkyboxDropdown.Value
    UpdateSkybox()
end)

WorldFogBox:AddLabel("Fog Color"):AddColorPicker("FogColorPicker", { Default = Lighting.FogColor })
Options.FogColorPicker:OnChanged(function()
    Lighting.FogColor = Options.FogColorPicker.Value
end)

WorldFogBox:AddSlider("FogStartSlider", { Text = "Fog Start Distance", Default = Lighting.FogStart, Min = 0, Max = 5000, Rounding = 0 })
Options.FogStartSlider:OnChanged(function()
    Lighting.FogStart = Options.FogStartSlider.Value
end)

WorldFogBox:AddSlider("FogEndSlider", { Text = "Fog End Distance", Default = Lighting.FogEnd, Min = 0, Max = 10000, Rounding = 0 })
Options.FogEndSlider:OnChanged(function()
    Lighting.FogEnd = Options.FogEndSlider.Value
end)

WorldRightBox:AddSlider("BlurSlider", { Text = "World Blur Effect", Default = 1, Min = 1, Max = 5, Rounding = 1 })
Options.BlurSlider:OnChanged(function()
    local blurValue = Options.BlurSlider.Value
    local blurEffect = Lighting:FindFirstChild("hooksenseWorldBlur")
    if blurValue > 1 then
        if not blurEffect then
            blurEffect = Instance.new("BlurEffect")
            blurEffect.Name = "hooksenseWorldBlur"
            blurEffect.Parent = Lighting
        end
        blurEffect.Size = blurValue * 8
    else
        if blurEffect then blurEffect:Destroy() end
    end
end)

WorldRightBox:AddSlider("FpsCapSlider", { Text = "FPS Cap Limit", Default = 60, Min = 60, Max = 999, Rounding = 0 })
Options.FpsCapSlider:OnChanged(function()
    if setfpscap then setfpscap(Options.FpsCapSlider.Value) end
end)

WorldRightBox:AddDropdown("WeatherDropdown", { Text = "Select Weather Environment", Values = {"Clear Sky", "Rain Mode", "Snow Mode"}, Default = 1, Multi = false })
Options.WeatherDropdown:OnChanged(function()
    local SelectedWeather = Options.WeatherDropdown.Value
    if CurrentWeatherEffect then
        CurrentWeatherEffect:Destroy()
        CurrentWeatherEffect = nil
    end
    if SelectedWeather == "Rain Mode" then
        local assetId = "rbxassetid://11552439884"
        local success, result = pcall(function() return game:GetObjects(assetId)[1] end)
        if success and result and (result:IsA("ParticleEmitter") or result:IsA("Instance")) then
            CurrentWeatherEffect = result:Clone()
            CurrentWeatherEffect.Name = "hooksenseRainEmitter"
            CurrentWeatherEffect.Parent = Camera
        else
            CurrentWeatherEffect = Instance.new("ParticleEmitter")
            CurrentWeatherEffect.Name = "hooksenseRainEmitter"
            CurrentWeatherEffect.Texture = assetId
            CurrentWeatherEffect.Lifetime = NumberRange.new(2, 4)
            CurrentWeatherEffect.Speed = NumberRange.new(40, 80)
            CurrentWeatherEffect.Rate = 250
            CurrentWeatherEffect.VelocityDirection = Enum.VelocityDirection.Top
            CurrentWeatherEffect.Rotation = NumberRange.new(-15, 15)
            CurrentWeatherEffect.Size = NumberSequence.new(1.5)
            CurrentWeatherEffect.Transparency = NumberSequence.new(0.3)
            CurrentWeatherEffect.Acceleration = Vector3.new(0, -50, 0)
            CurrentWeatherEffect.Parent = Camera
        end
    elseif SelectedWeather == "Snow Mode" then
        local assetId = "rbxassetid://4547273363"
        local success, result = pcall(function() return game:GetObjects(assetId)[1] end)
        if success and result and (result:IsA("ParticleEmitter") or result:IsA("Instance")) then
            CurrentWeatherEffect = result:Clone()
            CurrentWeatherEffect.Name = "hooksenseSnowEmitter"
            CurrentWeatherEffect.Parent = Camera
        else
            CurrentWeatherEffect = Instance.new("ParticleEmitter")
            CurrentWeatherEffect.Name = "hooksenseSnowEmitter"
            CurrentWeatherEffect.Texture = assetId
            CurrentWeatherEffect.Lifetime = NumberRange.new(4, 7)
            CurrentWeatherEffect.Speed = NumberRange.new(10, 25)
            CurrentWeatherEffect.Rate = 120
            CurrentWeatherEffect.VelocityDirection = Enum.VelocityDirection.Top
            CurrentWeatherEffect.Rotation = NumberRange.new(0, 360)
            CurrentWeatherEffect.Size = NumberSequence.new(0.8)
            CurrentWeatherEffect.Transparency = NumberSequence.new(0.1)
            CurrentWeatherEffect.Acceleration = Vector3.new(0, -5, 0)
            CurrentWeatherEffect.Parent = Camera
        end
    end
end)

local BlacklistPlayersGroup = Tabs.Addons:AddLeftGroupbox("loaders Scripts")
BlacklistPlayersGroup:AddButton({ Text = "load walkspeed", Func = function()
    local success, err = pcall(function()
        loadstring(game:HttpGet('https://raw.githubusercontent.com/19mdSkibidi/19sMooze-Mobile-Rework/refs/heads/main/Mooze%20Mob'))()
    end)
    if success then
        Library:Notify("successfully!")
    else
        Library:Notify("Error loading script: " .. tostring(err))
    end
end })

BlacklistPlayersGroup:AddButton({ Text = "load drawing esp", Func = function()
    local success, err = pcall(function()
        loadstring(game:HttpGet("https://raw.githubusercontent.com/xqmt/Drawing-Esp-/refs/heads/main/99"))()
    end)
    if success then
        Library:Notify("successfully!")
    else
        Library:Notify("Error loading script: " .. tostring(err))
    end
end })


local InterfaceGroup = Tabs['UI']:AddLeftGroupbox("Global Font Customization")
local MenuGroup = Tabs['UI']:AddLeftGroupbox("Menu Settings")
local AppearanceGroup = Tabs['UI']:AddRightGroupbox("UI Appearance Customization")

InterfaceGroup:AddDropdown("GlobalFontDropdown", { Text = "Select Script Font", Values = RobloxFontsList, Default = table.find(RobloxFontsList, "Cartoon") or 1, Multi = false })
Options.GlobalFontDropdown:OnChanged(function()
    local SelectedFontEnum = Enum.Font[Options.GlobalFontDropdown.Value]
    if not SelectedFontEnum then return end
    _G.GlobalFontSetting = SelectedFontEnum
    if DisplayNameLabel and UsernameLabel and UserIdLabel then
        DisplayNameLabel.Font = SelectedFontEnum
        UsernameLabel.Font = SelectedFontEnum
        UserIdLabel.Font = SelectedFontEnum
    end
    for _, espComponents in pairs(ESP_Storage) do
        if espComponents.NameTag and espComponents.HealthTag then
            espComponents.NameTag.Font = SelectedFontEnum
            espComponents.HealthTag.Font = SelectedFontEnum
        end
    end
    for _, notifyFrame in ipairs(ActiveNotifications) do
        local textObj = notifyFrame:FindFirstChild("NotifyTextLabel")
        if textObj and textObj:IsA("TextLabel") then
            textObj.Font = SelectedFontEnum
        end
    end
end)

AppearanceGroup:AddDropdown("UIFontDropdown", { Text = "UI Custom Font", Values = RobloxFontsList, Default = table.find(RobloxFontsList, "Cartoon") or 1, Multi = false })
Options.UIFontDropdown:OnChanged(function()
    local targetFont = Enum.Font[Options.UIFontDropdown.Value]
    if not targetFont then return end
    if Library.ScreenGui then
        for _, desc in ipairs(Library.ScreenGui:GetDescendants()) do
            if desc:IsA("TextLabel") or desc:IsA("TextButton") or desc:IsA("TextBox") then
                desc.Font = targetFont
            end
        end
    else
        if Library.Main then
            for _, desc in ipairs(Library.Main:GetDescendants()) do
                if desc:IsA("TextLabel") or desc:IsA("TextButton") or desc:IsA("TextBox") then
                    desc.Font = targetFont
                end
            end
        end
        if Library.KeybindFrame then
            for _, desc in ipairs(Library.KeybindFrame:GetDescendants()) do
                if desc:IsA("TextLabel") or desc:IsA("TextButton") then
                    desc.Font = targetFont
                end
            end
        end
    end
end)

MenuGroup:AddToggle("KeybindMenuOpen", { Default = false, Text = "Open Keybind Menu", Callback = function(value) Library.KeybindFrame.Visible = value end})
MenuGroup:AddToggle("ShowCustomCursor", {Text = "Custom Cursor", Default = true, Callback = function(Value) Library.ShowCustomCursor = Value end})
MenuGroup:AddDivider()
MenuGroup:AddLabel("Menu bind"):AddKeyPicker("MenuKeybind", { Default = "RightShift", NoUI = true, Text = "Menu keybind" })

MenuGroup:AddButton("Unload", function() Library:Unload() end)
Library.ToggleKeybind = Options.MenuKeybind
Library:OnUnload(function()
    Library.Unloaded = true
end)

ThemeManager:SetLibrary(Library)
SaveManager:SetLibrary(Library)
SaveManager:IgnoreThemeSettings()
SaveManager:SetIgnoreIndexes({ "MenuKeybind" })
ThemeManager:SetFolder("hooksense")
SaveManager:SetFolder("hooksense/configs")
SaveManager:BuildConfigSection(Tabs['UI'])
ThemeManager:ApplyToTab(Tabs['UI'])
SaveManager:LoadAutoloadConfig()
