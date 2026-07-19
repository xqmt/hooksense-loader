-- =============================================================
--  _    _  ____   ____  _  _  ____  _____ _   _  ____  _____ 
-- | |  | |/ __ \ / __ \| |/ // ___|| ____| \ | |/ ___|| ____|
-- | |__| | |  | | |  | | ' / \___ \|  _| |  \| \___ \|  _|   
-- |  __  | |__| | |__| | . \  ___) | |___| |\  |___) | |___  
-- |_|  |_|\____/ \____/|_|\_\|____/|_____|_| \_|____/|_____|
-- =============================================================
if not game:IsLoaded() then 
    game.Loaded:Wait()
end

-- ============================================================================
-- [1] ตรวจสอบและโหลดระบบ Adonis Bypass (ถ้า Executor รองรับ getnamecallmethod)
-- ============================================================================
if getnamecallmethod then
    local success, err = pcall(function()
        loadstring(game:HttpGet("https://raw.githubusercontent.com/Pixeluted/adoniscries/main/Source.lua", true))()
    end)
end

coroutine.wrap(function()
    local success, err = pcall(function()
        -- ใช้ hookmetamethod ที่ปลอดภัยกว่าการยัดค่าใส่ Metatable ตรงๆ
        if hookmetamethod then
            local oldNamecall
            oldNamecall = hookmetamethod(game, "__namecall", newcclosure(function(self, ...)
                if checkcaller() then return oldNamecall(self, ...) end
                
                local args = {...}
                local method = getnamecallmethod()
                
                -- รายชื่อ Remotes ที่เป็นระบบตรวจจับ (Anti-Cheat) ที่ต้องการบล็อก
                local blockedRemotes = {
                    ["TeleportDetect"] = true,
                    ["CHECKER_1"] = true,
                    ["CHECKER"] = true,
                    ["GUI_CHECK"] = true,
                    ["OneMoreTime"] = true,
                    ["checkingSPEED"] = true,
                    ["BANREMOTE"] = true,
                    ["PERMAIDBAN"] = true,
                    ["KICKREMOTE"] = true,
                    ["BR_KICKPC"] = true,
                    ["BR_KICKMOBILE"] = true
                }

                if method == "FireServer" or method == "InvokeServer" then
                    local remoteName = tostring(self.Name)
                    if blockedRemotes[remoteName] or (args[1] and blockedRemotes[tostring(args[1])]) then
                        return
                    end
                end

                return oldNamecall(self, ...)
            end))
        end
    end)

    -- แสดงแจ้งเตือนผลลัพธ์การ Hook บน Console
    if not success then
        warn("[Anti-RemoteBlock] Executor not support hookmetamethod. Skipped.")
    else
        warn("[+] hooksense.cc : anticheat bypassed.")
    end
end)()

-- ============================================================================
-- [2] โหลดและตั้งค่าโครงสร้าง UI Library (LinoriaLib)
-- ============================================================================
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
    NotifySide = "Right", 
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

-- ============================================================================
-- [3] การประกาศค่าตัวแปร Global (_G) ทั้งหมดของระบบ
-- ============================================================================
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

_G.CustomFOVValue = 70

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
_G.HitNotifyDuration = 2.5
_G.HitNotifyTransparency = 0.0
_G.HitNotifyFont = Enum.Font.Cartoon
_G.HitNotifyTemplate = "Hit {name} in the {part} for {dmg} dmg with {weapon}" 
_G.HitNotifyPosX = 50 
_G.HitNotifyPosY = 65 

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
_G.MotionBlurEnabled = false
_G.MotionBlurIntensity = 1.5

_G.BhopEnabled = false
_G.BhopSpeedMultiplier = 1.5

_G.TargetHudToggle = true
_G.TargetHudPosX = 0
_G.TargetHudPosY = 0
_G.TargetHudBorderColor1 = Color3.fromRGB(0, 255, 100)
_G.TargetHudBorderColor2 = Color3.fromRGB(0, 150, 0)
_G.TargetHudHealthHigh = Color3.fromRGB(0, 255, 100)
_G.TargetHudHealthMid = Color3.fromRGB(255, 200, 0)
_G.TargetHudHealthLow = Color3.fromRGB(255, 50, 50)

_G.AtmosphereEnabled = false 
_G.AtmosphereColor = Color3.fromRGB(178, 200, 255)
_G.AtmosphereDecay = Color3.fromRGB(255, 178, 120)
_G.AtmosphereGlare = 0.4
_G.AtmosphereHaze = 1.2
_G.AtmosphereOffset = 0.25
_G.AtmosphereDensity = 0.35

-- ============================================================================
-- [4] การจัดเตรียม Instance ทางฝั่ง Game Environment
-- ============================================================================
local Camera = workspace.CurrentCamera
local Players = game.Players
local LocalPlayer = Players.LocalPlayer
local CoreGui = game:GetService("CoreGui")
local UserInputService = game:GetService("UserInputService")
local SoundService = game:GetService("SoundService")
local Lighting = game:GetService("Lighting")
local TweenService = game:GetService("TweenService")
local DisplayNameLabel, UsernameLabel, UserIdLabel, AvatarImage
local ESP_Storage = {}

local TargetGuiParent = LocalPlayer:WaitForChild("PlayerGui", 5) or (CoreGui:FindFirstChild("RobloxGui") or CoreGui)

-- [Hit Overlay Setup]
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

-- [Hit Notification Setup]
local CenterNotifyGui = Instance.new("ScreenGui")
CenterNotifyGui.Name = "hooksense_CenterNotifyGui"
CenterNotifyGui.ResetOnSpawn = false
CenterNotifyGui.Parent = TargetGuiParent

local CenterNotifyContainer = Instance.new("Frame")
CenterNotifyContainer.Name = "NotifyContainer"
CenterNotifyContainer.Size = UDim2.new(0.6, 0, 0.4, 0)
CenterNotifyContainer.AnchorPoint = Vector2.new(0.5, 0.5)
CenterNotifyContainer.Position = UDim2.new(_G.HitNotifyPosX / 100, 0, _G.HitNotifyPosY / 100, 0)
CenterNotifyContainer.BackgroundTransparency = 1
CenterNotifyContainer.BorderSizePixel = 0
CenterNotifyContainer.Parent = CenterNotifyGui

local CenterNotifyLayout = Instance.new("UIListLayout")
CenterNotifyLayout.FillDirection = Enum.FillDirection.Vertical
CenterNotifyLayout.HorizontalAlignment = Enum.HorizontalAlignment.Center
CenterNotifyLayout.VerticalAlignment = Enum.VerticalAlignment.Bottom
CenterNotifyLayout.SortOrder = Enum.SortOrder.LayoutOrder
CenterNotifyLayout.Padding = UDim.new(0, 5)
CenterNotifyLayout.Parent = CenterNotifyContainer

local function ShowCustomHitNotification(targetName, partName, damage, weaponName)
    if not _G.HitNotifyEnabled then return end
    
    weaponName = weaponName or "Hands"
    
    local notifyText = _G.HitNotifyTemplate
    notifyText = string.gsub(notifyText, "{name}", targetName)
    notifyText = string.gsub(notifyText, "{part}", partName)
    notifyText = string.gsub(notifyText, "{dmg}", tostring(damage))
    notifyText = string.gsub(notifyText, "{weapon}", weaponName)
    
    local NotifyLabel = Instance.new("TextLabel")
    NotifyLabel.Size = UDim2.new(1, 0, 0, 24)
    NotifyLabel.BackgroundTransparency = 1
    NotifyLabel.Text = notifyText
    NotifyLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
    NotifyLabel.TextSize = 16
    NotifyLabel.Font = _G.HitNotifyFont
    NotifyLabel.TextStrokeColor3 = Color3.fromRGB(0, 0, 0)
    
    NotifyLabel.Position = UDim2.new(0, 0, 0, 15)
    NotifyLabel.TextTransparency = 1
    NotifyLabel.TextStrokeTransparency = 1
    NotifyLabel.Parent = CenterNotifyContainer

    local openTween = TweenService:Create(NotifyLabel, TweenInfo.new(0.35, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {
        Position = UDim2.new(0, 0, 0, 0),
        TextTransparency = _G.HitNotifyTransparency,
        TextStrokeTransparency = math.clamp(_G.HitNotifyTransparency + 0.4, 0, 1)
    })
    openTween:Play()

    task.delay(_G.HitNotifyDuration, function()
        if not NotifyLabel or not NotifyLabel.Parent then return end
        
        local closeTween = TweenService:Create(NotifyLabel, TweenInfo.new(0.4, Enum.EasingStyle.Quad, Enum.EasingDirection.In), {
            Position = UDim2.new(0, 0, 0, 25),
            TextTransparency = 1,
            TextStrokeTransparency = 1
        })
        closeTween:Play()
        closeTween.Completed:Connect(function()
            NotifyLabel:Destroy()
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

local function UpdateAtmosphere()
    local atmos = Lighting:FindFirstChildOfClass("Atmosphere")
    if _G.AtmosphereEnabled then
        if not atmos then
            atmos = Instance.new("Atmosphere")
            atmos.Parent = Lighting
        end
        atmos.Color = _G.AtmosphereColor
        atmos.Decay = _G.AtmosphereDecay
        atmos.Glare = _G.AtmosphereGlare
        atmos.Haze = _G.AtmosphereHaze
        atmos.Offset = _G.AtmosphereOffset
        atmos.Density = _G.AtmosphereDensity
        
        if not Lighting:FindFirstChildOfClass("Sky") then
            local DefaultSky = Instance.new("Sky")
            DefaultSky.Name = "hooksenseDefaultSky"
            DefaultSky.Parent = Lighting
        end
    else
        if atmos then
            atmos:Destroy()
        end
        if not _G.SkyboxEnabled then
            local defaultSky = Lighting:FindFirstChild("hooksenseDefaultSky")
            if defaultSky then
                defaultSky:Destroy()
            end
        end
    end
end

UpdateAtmosphere()

-- [Target HUD GUI Element Create]
local TargetGui = Instance.new("ScreenGui")
TargetGui.Name = "hooksenseTargetHudGui"
TargetGui.ResetOnSpawn = false
TargetGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
TargetGui.Parent = TargetGuiParent

local MainCanvas = Instance.new("CanvasGroup")
MainCanvas.Name = "MainTargetHUD"
MainCanvas.Size = UDim2.new(0, 280, 0, 90)
MainCanvas.AnchorPoint = Vector2.new(1, 0)
MainCanvas.Position = UDim2.new(1, -20, 0, 20)
MainCanvas.BackgroundColor3 = Color3.fromRGB(0, 0, 0)
MainCanvas.BackgroundTransparency = 0.15 
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
    ColorSequenceKeypoint.new(0, _G.TargetHudBorderColor1),
    ColorSequenceKeypoint.new(1, _G.TargetHudBorderColor2)
})
BorderGradient.Rotation = 45
BorderGradient.Parent = Stroke

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
HealthBar.BackgroundColor3 = _G.TargetHudHealthHigh
HealthBar.BorderSizePixel = 0
HealthBar.Parent = HealthBackground

local MainBarCorner = Instance.new("UICorner")
MainBarCorner.CornerRadius = UDim.new(0, 4)
MainBarCorner.Parent = HealthBar

local isHudVisible = false
local function ToggleHUD(state)
    if state and _G.TargetHudToggle then
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
TracerLineOutline.Thickness = 3.0
TracerLineOutline.Transparency = 1.0

local TracerLine = Drawing.new("Line")
TracerLine.Thickness = 1.0
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

-- ============================================================================
-- [5] ระบบการคำนวณและล็อกเป้าหมาย (Aimbot & Target Tracking Logic)
-- ============================================================================
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
        if CurrentTargetPlayer == targetPlayer and hum.Health < lastHealth then
            local damageCalculated = math.floor(lastHealth - hum.Health)
            task.spawn(PlayHitSound)
            task.spawn(TriggerHitOverlay) 
            local hitPartName = _G.TargetPartMode
            if hitPartName == "Root to Head" then
                hitPartName = "Body/Head"
            elseif hitPartName == "HumanoidRootPart" then
                hitPartName = "Torso"
            end
            
            local weaponName = "Hands"
            if LocalPlayer.Character then
                local heldTool = LocalPlayer.Character:FindFirstChildOfClass("Tool")
                if heldTool then
                    weaponName = heldTool.Name
                end
            end
            
            task.spawn(ShowCustomHitNotification, targetPlayer.Name, hitPartName, damageCalculated, weaponName)
        end
        lastHealth = hum.Health
    end)
end

-- ============================================================================
-- [6] ระบบ ESP & Rendering Loop
-- ============================================================================
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

local function ResetCamera()
    Camera.CameraType = Enum.CameraType.Custom
    local char = LocalPlayer.Character
    local hum = char and char:FindFirstChildOfClass("Humanoid")
    if hum then
        hum.CameraOffset = Vector3.new(0, 0, 0)
    end
    LocalPlayer.CameraMaxZoomDistance = 128
    LocalPlayer.CameraMinZoomDistance = 0.5
end

local RunService = game:GetService("RunService")
local spinAngle = 0
local jitterToggle = false
local LastLoggedHudTargetId = 0
local currentHudHealthLerp = 0 
local LastCameraRotation = Camera.CFrame.LookVector

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

    MainCanvas.Position = UDim2.new(1, -20 + _G.TargetHudPosX, 0, 20 + _G.TargetHudPosY)

    if (_G.SilentAimEnabled or _G.MobileAimbotEnabled) and CurrentTargetPlayer and CurrentTargetPlayer.Character and _G.TargetHudToggle then
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
            
            if currentHudHealthLerp > 0.6 then
                HealthBar.BackgroundColor3 = _G.TargetHudHealthHigh
            elseif currentHudHealthLerp > 0.3 then
                HealthBar.BackgroundColor3 = _G.TargetHudHealthMid
            else
                HealthBar.BackgroundColor3 = _G.TargetHudHealthLow
            end
            
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

    if _G.ThirdPersonEnabled then
        local char = LocalPlayer.Character
        local hum = char and char:FindFirstChildOfClass("Humanoid")
        if hum then
            hum.CameraOffset = Vector3.new(1.5, 2, 0)
            LocalPlayer.CameraMinZoomDistance = _G.ThirdPersonDistance
            LocalPlayer.CameraMaxZoomDistance = _G.ThirdPersonDistance
            if Camera.CameraType ~= Enum.CameraType.Custom then
                Camera.CameraType = Enum.CameraType.Custom
            end
        end
    else
        local char = LocalPlayer.Character
        local hum = char and char:FindFirstChildOfClass("Humanoid")
        if hum and hum.CameraOffset ~= Vector3.new(0, 0, 0) then
            ResetCamera()
        end
    end

    local blurEffect = Lighting:FindFirstChild("hooksenseMotionBlur")
    if _G.MotionBlurEnabled then
        if not blurEffect then
            blurEffect = Instance.new("BlurEffect")
            blurEffect.Name = "hooksenseMotionBlur"
            blurEffect.Parent = Lighting
        end
        local currentLookVector = Camera.CFrame.LookVector
        local angleDifference = math.acos(math.clamp(currentLookVector:Dot(LastCameraRotation), -1, 1))
        local blurTarget = math.clamp(angleDifference * 45 * _G.MotionBlurIntensity, 0, 56)
        
        blurEffect.Size = blurEffect.Size + (blurTarget - blurEffect.Size) * 0.25
        LastCameraRotation = currentLookVector
    else
        if blurEffect then blurEffect:Destroy() end
    end

    for player, v in pairs(ESP_Storage) do
        local char = player.Character
        local head = char and char:FindFirstChild("Head")
        local hrp = char and char:FindFirstChild("HumanoidRootPart")
        local humanoid = char and char:FindFirstChildOfClass("Humanoid")
        
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

-- ============================================================================
-- [7] Silent Aim Hook Metamethod (รันแยกส่วนกับระบบ Anti-Remote)
-- ============================================================================
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

-- ============================================================================
-- [8] การสร้าง Tabs เมนูและองค์ประกอบของ Linoria UI
-- ============================================================================
local Tabs = {
    Main = Window:AddTab("Main"),
    Aimbot = Window:AddTab("Aimbot"),
    HitEffects = Window:AddTab("Hits"),
    ESP = Window:AddTab("Esp"),
    Movement = Window:AddTab("Character"),
    World = Window:AddTab("World"),
    Addons = Window:AddTab("Misc"),
    ['UI'] = Window:AddTab("UI setting")
}

local Options = getgenv().Options
local Toggles = getgenv().Toggles

-- [Aimbot Tab Components]
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

-- [Main Tab Components]
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

Players.PlayerRemoving:Connect(function(player)
    task.wait(0.1)
    RefreshDropdownValues()
end)
Players.PlayerAdded:Connect(function(player)
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

-- [HitEffects Tab Components]
local SoundLeftBox = Tabs.HitEffects:AddLeftGroupbox("Hit Sound")
local OverlayLeftBox = Tabs.HitEffects:AddLeftGroupbox("Hit Overlay") 
local NotifyRightBox = Tabs.HitEffects:AddRightGroupbox("Hit Notification Custom System")

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

NotifyRightBox:AddToggle("HitNotifyToggle", { Text = "Enable Hit Notification", Default = false })
Toggles.HitNotifyToggle:OnChanged(function()
    _G.HitNotifyEnabled = Toggles.HitNotifyToggle.Value
end)

NotifyRightBox:AddSlider("HitNotifyDurationSlider", { Text = "Notification Duration (s)", Default = 2.5, Min = 0.5, Max = 5.0, Rounding = 1 })
Options.HitNotifyDurationSlider:OnChanged(function()
    _G.HitNotifyDuration = Options.HitNotifyDurationSlider.Value
end)

NotifyRightBox:AddSlider("HitNotifyTransparencySlider", { Text = "Notification Opacity/Transparency", Default = 0, Min = 0, Max = 1, Rounding = 2 })
Options.HitNotifyTransparencySlider:OnChanged(function()
    _G.HitNotifyTransparency = Options.HitNotifyTransparencySlider.Value
end)

NotifyRightBox:AddSlider("HitNotifyPosXSlider", { Text = "Position X Offset (%)", Default = 50, Min = 1, Max = 100, Rounding = 0 })
Options.HitNotifyPosXSlider:OnChanged(function()
    _G.HitNotifyPosX = Options.HitNotifyPosXSlider.Value
    CenterNotifyContainer.Position = UDim2.new(_G.HitNotifyPosX / 100, 0, _G.HitNotifyPosY / 100, 0)
end)

NotifyRightBox:AddSlider("HitNotifyPosYSlider", { Text = "Position Y Offset (%)", Default = 65, Min = 1, Max = 100, Rounding = 0 })
Options.HitNotifyPosYSlider:OnChanged(function()
    _G.HitNotifyPosY = Options.HitNotifyPosYSlider.Value
    CenterNotifyContainer.Position = UDim2.new(_G.HitNotifyPosX / 100, 0, _G.HitNotifyPosY / 100, 0)
end)

NotifyRightBox:AddDropdown("HitNotifyFontDropdown", { Text = "Hit Notify Custom Font", Values = RobloxFontsList, Default = table.find(RobloxFontsList, "Cartoon") or 1, Multi = false })
Options.HitNotifyFontDropdown:OnChanged(function()
    local SelectedFont = Enum.Font[Options.HitNotifyFontDropdown.Value]
    if SelectedFont then
        _G.HitNotifyFont = SelectedFont
    end
end)

NotifyRightBox:AddInput("CustomHitNotifyInput", { Placeholder = "Format: {name} | {part} | {dmg} | {weapon}", Text = "Hit {name} in the {part} for {dmg} dmg with {weapon}", Numeric = false, Finished = true })
Options.CustomHitNotifyInput:OnChanged(function()
    if Options.CustomHitNotifyInput.Value and Options.CustomHitNotifyInput.Value ~= "" then
        _G.HitNotifyTemplate = Options.CustomHitNotifyInput.Value
    end
end)

-- [ESP Tab Components]
local EspLeftBox = Tabs.ESP:AddLeftGroupbox("Visuals Control")
local EspRightBox = Tabs.ESP:AddRightGroupbox("Color Customization")

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

-- [Movement Tab Components]
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

-- [World Tab Components]
local LightingColorsGroup = Tabs.World:AddLeftGroupbox("Lighting Colors & Time")
local WorldSkyboxBox = Tabs.World:AddLeftGroupbox("Custom Skybox System")
local WorldFogBox = Tabs.World:AddLeftGroupbox("World Fog Customization")
local WorldAtmosphereBox = Tabs.World:AddLeftGroupbox("World Atmosphere Customization")
local CameraDisplayBox = Tabs.World:AddRightGroupbox("Camera & Display Settings")

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

WorldSkyboxBox:AddDropdown("SkyboxDropdown", { Text = "Select Skybox", Values = {"Minecraft", "Minecraft 2", "Skyblox 1", "Skyblox 2", "Skyblox 3", "Skyblox 4"}, Default = 1, Multi = false })
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

WorldAtmosphereBox:AddToggle("AtmosphereToggle", { Text = "Enable Atmosphere", Default = false })
Toggles.AtmosphereToggle:OnChanged(function()
    _G.AtmosphereEnabled = Toggles.AtmosphereToggle.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddLabel("Tint Color"):AddColorPicker("AtmosColorPicker", { Default = _G.AtmosphereColor })
Options.AtmosColorPicker:OnChanged(function()
    _G.AtmosphereColor = Options.AtmosColorPicker.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddLabel("Decay Color"):AddColorPicker("AtmosDecayPicker", { Default = _G.AtmosphereDecay })
Options.AtmosDecayPicker:OnChanged(function()
    _G.AtmosphereDecay = Options.AtmosDecayPicker.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddSlider("AtmosGlareSlider", { Text = "Glare Intensity", Default = _G.AtmosphereGlare, Min = 0.1, Max = 10, Rounding = 1 })
Options.AtmosGlareSlider:OnChanged(function()
    _G.AtmosphereGlare = Options.AtmosGlareSlider.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddSlider("AtmosHazeSlider", { Text = "Haze Density", Default = _G.AtmosphereHaze, Min = 0.1, Max = 10, Rounding = 1 })
Options.AtmosHazeSlider:OnChanged(function()
    _G.AtmosphereHaze = Options.AtmosHazeSlider.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddSlider("AtmosOffsetSlider", { Text = "Horizon Offset", Default = _G.AtmosphereOffset, Min = 0.01, Max = 1, Rounding = 2 })
Options.AtmosOffsetSlider:OnChanged(function()
    _G.AtmosphereOffset = Options.AtmosOffsetSlider.Value
    UpdateAtmosphere()
end)

WorldAtmosphereBox:AddSlider("AtmosDensitySlider", { Text = "Atmosphere Density", Default = _G.AtmosphereDensity, Min = 0.01, Max = 1, Rounding = 2 })
Options.AtmosDensitySlider:OnChanged(function()
    _G.AtmosphereDensity = Options.AtmosDensitySlider.Value
    UpdateAtmosphere()
end)

CameraDisplayBox:AddSlider("CustomFovSlider", { Text = "Custom FOV", Default = 70, Min = 70, Max = 120, Rounding = 0 })
Options.CustomFovSlider:OnChanged(function()
    _G.CustomFOVValue = Options.CustomFovSlider.Value
    Camera.FieldOfView = _G.CustomFOVValue
end)

Camera:GetPropertyChangedSignal("FieldOfView"):Connect(function()
    if Camera.FieldOfView ~= _G.CustomFOVValue then
        Camera.FieldOfView = _G.CustomFOVValue
    end
end)

CameraDisplayBox:AddSlider("BlurSlider", { Text = "World Blur", Default = 0, Min = 0, Max = 5, Rounding = 1 })
Options.BlurSlider:OnChanged(function()
    local blurValue = Options.BlurSlider.Value
    local blurEffect = Lighting:FindFirstChild("hooksenseWorldBlur")
    if blurValue > 0 then
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

CameraDisplayBox:AddToggle("MotionBlurToggle", { Text = "Enable Motion Blur", Default = false })
Toggles.MotionBlurToggle:OnChanged(function()
    _G.MotionBlurEnabled = Toggles.MotionBlurToggle.Value
end)

CameraDisplayBox:AddSlider("MotionBlurIntensitySlider", { Text = "Motion Blur Intensity", Default = 1.5, Min = 0.5, Max = 5.0, Rounding = 1 })
Options.MotionBlurIntensitySlider:OnChanged(function()
    _G.MotionBlurIntensity = Options.MotionBlurIntensitySlider.Value
end)

CameraDisplayBox:AddSlider("FpsCapSlider", { Text = "FPS Cap Limit", Default = 60, Min = 60, Max = 999, Rounding = 0 })
Options.FpsCapSlider:OnChanged(function()
    if setfpscap then setfpscap(Options.FpsCapSlider.Value) end
end)

-- [Addons Tab Components]
local BlacklistPlayersGroup = Tabs.Addons:AddLeftGroupbox("loaders Scripts")
local TargetHudConfigGroup = Tabs.Addons:AddRightGroupbox("Target HUD Settings")

TargetHudConfigGroup:AddToggle("TargetHudMasterToggle", { Text = "Enable Target HUD", Default = true })
Toggles.TargetHudMasterToggle:OnChanged(function()
    _G.TargetHudToggle = Toggles.TargetHudMasterToggle.Value
end)

TargetHudConfigGroup:AddSlider("TargetHudPosXSlider", { Text = "Position X Offset", Default = 0, Min = -1000, Max = 1000, Rounding = 0 })
Options.TargetHudPosXSlider:OnChanged(function()
    _G.TargetHudPosX = Options.TargetHudPosXSlider.Value
end)

TargetHudConfigGroup:AddSlider("TargetHudPosYSlider", { Text = "Position Y Offset", Default = 0, Min = -1000, Max = 1000, Rounding = 0 })
Options.TargetHudPosYSlider:OnChanged(function()
    _G.TargetHudPosY = Options.TargetHudPosYSlider.Value
end)

TargetHudConfigGroup:AddLabel("Border Color 1"):AddColorPicker("HudBorderColor1Picker", { Default = Color3.fromRGB(0, 255, 100) })
Options.HudBorderColor1Picker:OnChanged(function()
    _G.TargetHudBorderColor1 = Options.HudBorderColor1Picker.Value
    BorderGradient.Color = ColorSequence.new({
        ColorSequenceKeypoint.new(0, _G.TargetHudBorderColor1),
        ColorSequenceKeypoint.new(1, _G.TargetHudBorderColor2)
    })
end)

TargetHudConfigGroup:AddLabel("Border Color 2"):AddColorPicker("HudBorderColor2Picker", { Default = Color3.fromRGB(0, 150, 0) })
Options.HudBorderColor2Picker:OnChanged(function()
    _G.TargetHudBorderColor2 = Options.HudBorderColor2Picker.Value
    BorderGradient.Color = ColorSequence.new({
        ColorSequenceKeypoint.new(0, _G.TargetHudBorderColor1),
        ColorSequenceKeypoint.new(1, _G.TargetHudBorderColor2)
    })
end)

TargetHudConfigGroup:AddLabel("Health Color: High (>60%)"):AddColorPicker("HudHealthHighPicker", { Default = Color3.fromRGB(0, 255, 100) })
Options.HudHealthHighPicker:OnChanged(function()
    _G.TargetHudHealthHigh = Options.HudHealthHighPicker.Value
end)

TargetHudConfigGroup:AddLabel("Health Color: Medium (30%-60%)"):AddColorPicker("HudHealthMidPicker", { Default = Color3.fromRGB(255, 200, 0) })
Options.HudHealthMidPicker:OnChanged(function() 
    _G.TargetHudHealthMid = Options.HudHealthMidPicker.Value
end)

TargetHudConfigGroup:AddLabel("Health Color: Low (<30%)"):AddColorPicker("HudHealthLowPicker", { Default = Color3.fromRGB(255, 50, 50) })
Options.HudHealthLowPicker:OnChanged(function()
    _G.TargetHudHealthLow = Options.HudHealthLowPicker.Value
end)

BlacklistPlayersGroup:AddButton({ Text = "walkspeed", Func = function()
    local success, err = pcall(function()
        loadstring(game:HttpGet('https://raw.githubusercontent.com/19mdSkibidi/19sMooze-Mobile-Rework/refs/heads/main/Mooze%20Mob'))()
    end)
    if success then
        Library:Notify("successfully!")
    else
        Library:Notify("Error loading script: " .. tostring(err))
    end
end })

BlacklistPlayersGroup:AddButton({ Text = "drawing esp", Func = function()
    local success, err = pcall(function()
        loadstring(game:HttpGet("https://raw.githubusercontent.com/xqmt/Drawing-Esp-/refs/heads/main/99"))()
    end)
    if success then
        Library:Notify("successfully!")
    else
        Library:Notify("Error loading script: " .. tostring(err))
    end
end })

-- [UI Tab Components]
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
end)

-- ============================================================================
-- [9] ระบบลงทะเบียนและโหลดตัวจัดการธีม / เซฟไฟล์ (Theme & Save Manager Settings)
-- ============================================================================
MenuGroup:AddButton({ Text = "Unload Script", Func = function() Library:Unload() end })
MenuGroup:AddLabel("Menu Keybind"):AddKeyPicker("MenuKeybind", { Default = "End", NoUI = true, Text = "Menu Keybind" })

ThemeManager:SetLibrary(Library)
SaveManager:SetLibrary(Library)

ThemeManager:SetFolder("hooksense")
SaveManager:SetFolder("hooksense/configs")

SaveManager:BuildConfigSection(Tabs['UI'])
ThemeManager:ApplyToTab(Tabs['UI'])

SaveManager:LoadAutoloadConfig()
