#include "PlayList.h"
#include<iostream>
#include <VersionHelpers.h>		//用于判断当前Windows的版本

int main()
{
	CPlayer my_player;
	my_player.ShowInfo();
	my_player.ShowPlaylist();
	while(!my_player.ErrorDispose());
	my_player.MusicControl(Command::OPEN);
	my_player.IniLyrics();
	my_player.MusicControl(Command::SEEK);
	my_player.ShowProgressBar();
	my_player.SetVolume();
	int sec_current, sec_temp;		//用于控制界面信息刷新频率，当前歌曲进度每过1秒刷新
	sec_temp = my_player.GetCurrentSecond();
	SYSTEMTIME current_time, temp_time;		//用于控制歌词刷新频率，歌词每过LYRIC_REFRESH毫秒刷新
	int width(0), hight(0);
	int width_t, hight_t;
	GetLocalTime(&temp_time);
	while (true)
	{
		while(!my_player.ErrorDispose());
		my_player.GetCurrentPosition();
		sec_current = my_player.GetCurrentSecond();
		if (sec_temp != sec_current)		//获取播放时间的秒数，如果秒数变了则刷新一次界面信息
		{
			sec_temp = sec_current;
			my_player.GetCurrentPosition();
			my_player.ShowInfo();
			//my_player.ShowPlaylist();
			my_player.ShowProgressBar();
			//my_player.ShowLyrics();
			//my_player.SaveConfig();
		}
		GetLocalTime(&current_time);
		if (current_time - temp_time > LYRIC_REFRESH && my_player.IsPlaying())		//如果当前时间与之前的时间差超过了LYRIC_REFRESH毫秒，并且正在播放，就刷新一次歌词
		{
			temp_time = current_time;
			my_player.ShowLyrics();
		}
		if (my_player.SongIsOver())
		{
			if (!my_player.PlayTrack(NEXT))		//顺序播放模式下列表中的歌曲播放完毕，PlayTrack函数会返回false
				my_player.MusicControl(Command::STOP);		//停止播放
		}
		if (_kbhit())
		{
			switch (GetKey())
			{
			//case 'P': my_player.MusicControl(Command::PLAY); break;
			case 'P': case SPACE_KEY: my_player.MusicControl(Command::PLAY_PAUSE); break;		//播放/暂停
			case 'S': my_player.MusicControl(Command::STOP); break;		//停止
			case 'N': my_player.PlayTrack(NEXT); break;		//下一曲
			case 'V': my_player.PlayTrack(PREVIOUS); break;		//上一曲
			case RIGHT_KEY: my_player.MusicControl(Command::FF); break;		//快进
			case LEFT_KEY:my_player.MusicControl(Command::REW); break;		//快退
			case 'T': my_player.SetPath(); break;		//设置路径
			case UP_KEY: my_player.MusicControl(Command::VOLUME_UP); break;		//音量加
			case DOWN_KEY:my_player.MusicControl(Command::VOLUME_DOWN); break;		//音量减
			case 'K': my_player.SetTrack(); break;		//播放指定歌曲
			case '[': my_player.SwitchPlaylist(PREVIOUS); break;		//播放列表向前翻页
			case ']': my_player.SwitchPlaylist(NEXT); break;			//播放列表向后翻页
			case 'M': my_player.SetRepeatMode(); break;			//切换循环模式
			//case 'L': my_player.ConvertLyric(); break;
			case ESC_KEY:
				//my_player.GetConsoleSetting();
				my_player.SaveConfig();
				return 0;
			}
			my_player.ShowInfo();
			my_player.ShowProgressBar();
			my_player.ShowLyrics(true);
			my_player.ShowPlaylist();
		}

		width_t = GetWindowWidth();
		hight_t = GetWindowHight();
		if (width != width_t || hight != hight_t)		//如果控制台窗口大小发生改变
		{
			width = width_t;
			hight = hight_t;
			if (width_t >= MIN_WIDTH && hight_t >= MIN_HIGHT)		//确保设定的窗口大小不会小于最小值
			{
				//如果系统是windows10，宽度改变后重新将控制台缓冲区大小设置为窗口大小，可以使控制台窗口大小调整后不会显示滚动条。
				//而Windws10以下的系统无法通过改变窗口大小来改变缓冲区大小，这样会导致窗口调小后无法调大，所以不应该在
				//改变窗口大小的时候重设缓冲区大小。
				//（VS2013没有判断win10以上的函数，这里用win8以上代替，用以区别win7）
				if (IsWindows8OrGreater())
				{
					char buff[32];
					sprintf_s(buff, 31, "mode con:cols=%d lines=%d", width_t, hight_t);
					system(buff);		//设置窗口的宽度和高度
				}

				my_player.GetWindowsSize(width_t, hight_t);
				//控制台窗口大小改变时重新刷新信息
				system("cls");
				my_player.ShowInfo();
				my_player.ShowProgressBar();
				my_player.ShowLyrics(true);
				my_player.ShowPlaylist();
				my_player.SaveConfig();
			}
			else
			{
				//windows10
				if (IsWindows8OrGreater())
				{
					char buff[32];
					sprintf_s(buff, 31, "mode con:cols=%d lines=%d", MIN_WIDTH, MIN_HIGHT);
					system(buff);		//设置窗口的宽度和高度
				}
			}
		}
		Sleep(20);			//降低主函数循环执行的频率，以减小CPU利用率
	}
}