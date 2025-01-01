using UnityEngine;
using UnityEngine.Advertisements;

public class AdsManager : MonoBehaviour, IUnityAdsInitializationListener, IUnityAdsLoadListener, IUnityAdsShowListener
{
    public string gameid = "gameid";
    public bool TestMode = true;

    private string BannerPlacementID = "Banner_Android";
    private BannerOptions options;

    private void Start()
    {
        Advertisement.Initialize(gameid, TestMode, this);
        options = new BannerOptions
        {
            showCallback = OnBannerShown,
            hideCallback = OnBannerHidden
        };

        if (Application.internetReachability == NetworkReachability.NotReachable)
        {
            Debug.LogError("No internet connection.");
        }
        else
        {
            Debug.Log("Has internet connection.");
        }
    }

    public void OnInitializationComplete()
    {
        LoadBanner();
    }

    public void OnInitializationFailed(UnityAdsInitializationError error, string message)
    {
        Debug.Log("Unity Ads Initialization Failed:" + error.ToString() + message.ToString());
    }

    private void LoadBanner()
    {
        Advertisement.Load(BannerPlacementID, this);
    }

    public void OnUnityAdsAdLoaded(string placementId)
    {
        Debug.Log("Banner loaded: " + placementId.ToString());
        ShowBanner();
    }

    public void OnUnityAdsFailedToLoad(string placementId, UnityAdsLoadError error, string message)
    {
        Debug.Log("Banner failed to load: " + placementId.ToString() + error.ToString() + message.ToString());
    }

    private void ShowBanner()
    {
        Advertisement.Banner.SetPosition(BannerPosition.BOTTOM_CENTER);
        Advertisement.Banner.Show(BannerPlacementID, options);
    }

    public void OnUnityAdsShowFailure(string placementId, UnityAdsShowError error, string message)
    {
        Debug.Log("Banner show failed: " + placementId.ToString() + error.ToString() + message.ToString());
    }

    public void OnUnityAdsShowStart(string placementId)
    {
        Debug.Log("Banner showing: " + placementId.ToString());
    }

    public void OnUnityAdsShowClick(string placementId)
    {
        Debug.Log("Banner clicked: " + placementId.ToString());
    }

    public void OnUnityAdsShowComplete(string placementId, UnityAdsShowCompletionState showCompletionState)
    {
        Debug.Log("Banner show completed: " + placementId.ToString() + "result: " + showCompletionState.ToString());
        LoadBanner();
    }

    private void OnBannerShown()
    {
        Debug.Log("Banner shown.");
    }

    private void OnBannerHidden()
    {
        Debug.Log("Banner hidden.");
    }
}
