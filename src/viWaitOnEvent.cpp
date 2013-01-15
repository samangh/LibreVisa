/* 
 * Copyright (C) 2013 Simon Richter
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "visa.h"

#include "object_cache.h"
#include "session.h"

using namespace librevisa;

ViStatus viWaitOnEvent(
        ViSession vi,
        ViEventType inEventType,
        ViUInt32 timeout,
        ViPEventType outEventType,
        ViPEvent outContext)
{
        try
        {
                return objects.get_session(vi)->WaitOnEvent(inEventType, timeout, outEventType, outContext);
        }
        catch(exception &e)
        {
                return e.code;
        }
}
